/*********************************************************************************/
/* Module Name:  abp.c                                                           */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024 Jozef Nagy                                                 */
/*                                                                               */
/* This source is subject to the MIT License.                                    */
/* See License.txt in the root of this repository.                               */
/* All other rights reserved.                                                    */
/*                                                                               */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE.                                                                     */
/*********************************************************************************/

#include <arch/cpu/cpu.h>
#include <arch/mm/paging.h>
#include <protocol/abp.h>
#include <loader/elf.h>
#include <firmware/hwmgmnt.h>
#include <firmware/memmap.h>
#include <firmware/handoff.h>
#include <firmware/fb.h>
#include <lib/string.h>
#include <print.h>
#include <axboot.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

static void translate_memory_map(struct memory_map_info *memmap, struct abp_memory_map **abp_memmap)
{
    struct abp_memory_map *current_entry = *abp_memmap;
    current_entry = (struct abp_memory_map *)malloc(sizeof(struct abp_memory_map));

    for (size_t i = 0; i <= memmap->entry_count; i++) {
        current_entry->base = memmap->entries[i].base;
        current_entry->length = memmap->entries[i].length;
        
        switch (memmap->entries[i].type) {
            case MemoryMapUnusable:
            case MemoryMapReserved:
                current_entry->type = ABP_MEMORY_RESERVED;
                break;
            case MemoryMapUsable:
                current_entry->type = ABP_MEMORY_USABLE;
                break;
            case MemoryMapLoader:
                current_entry->type = ABP_MEMORY_BOOTLOADER_RECLAIMABLE;
                break;
            case MemoryMapAcpiReclaimable:
                current_entry->type = ABP_MEMORY_ACPI_RECLAIMABLE;
                break;
            case MemoryMapAcpiNVS:
                current_entry->type = ABP_MEMORY_ACPI_NVS;
                break;
            case MemoryMapMmio:
                current_entry->type = ABP_MEMORY_MMIO;
                break;
            default:
                debug("Unknown memory type 0x%x\r\n", memmap->entries[i].type);
                current_entry->type = ABP_MEMORY_RESERVED;
                break;
        }

        current_entry->next = (struct abp_memory_map *)malloc(sizeof(struct abp_memory_map));
        current_entry = current_entry->next;
    }

    current_entry->next = NULL;
}

void abp_load(void *kernel, size_t kernel_size)
{
    bool higher_half = false;
    void *kernel_entry;

    // acquire memory map and initialize paging
    struct memory_map_info memmap = {0};
    fw_get_memory_map(&memmap);
    memmap_dump(&memmap);

    if (paging_init(&memmap) != 0) {
        log("ERROR: Couldn't set up paging!\r\n");
        while(1);
    }

    struct abp_boot_info *boot_info = paging_allocate((sizeof(struct abp_boot_info) + PAGE_SIZE - 1) / PAGE_SIZE);

    debug("kernel buffer: 0x%llx\r\n", kernel);

    // get kernel entry point
    if (!elf_load(kernel, &kernel_entry)) {
        return;
    }

    // remap kernel to higher half if desired
    debug("kernel size: %u (%u pages)\r\n", kernel_size, (kernel_size + (PAGE_SIZE - 1)) / PAGE_SIZE);
    for (uint64_t i = 0; i < (kernel_size + (PAGE_SIZE - 1)) / PAGE_SIZE; i++) {
        paging_identity_map((uint64_t)kernel + (i * PAGE_SIZE));
        paging_map((uint64_t)kernel + (i * PAGE_SIZE), HIGHER_HALF + (i * PAGE_SIZE));
    }

    kernel_entry += HIGHER_HALF;

    // set up basic boot information
    boot_info->bootloader_name = paging_allocate((strlen(BOOTLOADER_NAME_STR) + PAGE_SIZE - 1) / PAGE_SIZE);
    boot_info->bootloader_version = paging_allocate((strlen(BOOTLOADER_VERSION_STR) + PAGE_SIZE - 1) / PAGE_SIZE);
    boot_info->protocol_version = paging_allocate((strlen(AXBOOT_PROTOCOL_VERSION_STR) + PAGE_SIZE - 1) / PAGE_SIZE);
    strcpy(boot_info->bootloader_name, BOOTLOADER_NAME_STR);
    strcpy(boot_info->bootloader_version, BOOTLOADER_VERSION_STR);
    strcpy(boot_info->protocol_version, AXBOOT_PROTOCOL_VERSION_STR);

    // get ACPI and SMBIOS info
    boot_info->acpi.rsdp = fw_get_acpi_rsdp();
    if (boot_info->acpi.rsdp != NULL) {
        boot_info->acpi.is_valid = 1;
    }

    boot_info->smbios.entry_point = fw_get_smbios_entry_point();
    if (boot_info->smbios.entry_point != NULL) {
        boot_info->smbios.is_valid = 1;
    }

    // get framebuffer info
    fw_get_framebuffer(&boot_info->framebuffer.addr, &boot_info->framebuffer.width, &boot_info->framebuffer.height, &boot_info->framebuffer.bpp, &boot_info->framebuffer.pixel_format);
    if (boot_info->framebuffer.pixel_format == 1) {
        boot_info->framebuffer.pixel_format = AbpFramebufferRgba;
    } else if (boot_info->framebuffer.pixel_format == 2) {
        boot_info->framebuffer.pixel_format = AbpFramebufferBgra;
    }

    // identity map the framebuffer
    uint64_t framebuffer_size = boot_info->framebuffer.width * boot_info->framebuffer.height * (boot_info->framebuffer.bpp >> 3);
    debug("Identity mapping the framebuffer...\r\n");
    for (uint64_t i = 0; i < (framebuffer_size + (PAGE_SIZE - 1)) / PAGE_SIZE; i++) {
        paging_identity_map((uint64_t)boot_info->framebuffer.addr + (i * PAGE_SIZE));
    }

    debug("Framebuffer info:\r\n");
    debug("- Address: 0x%llx\r\n", boot_info->framebuffer.addr);
    debug("- Width: %u\r\n", boot_info->framebuffer.width);
    debug("- Height: %u\r\n", boot_info->framebuffer.height);
    debug("- Bits per pixel: %u\r\n", boot_info->framebuffer.bpp);
    debug("- Pixel Format: %s\r\n", boot_info->framebuffer.pixel_format == AbpFramebufferRgba ? "RGBA" : "BGRA");
    
    // create a new 64 KB stack for the kernel
    void *kernel_stack = paging_allocate(16);
    memset(kernel_stack, 0, (16 * PAGE_SIZE));
    debug("Created new stack at 0x%lx\r\n", kernel_stack);

    for (uint64_t i = 0; i < 16; i++) {
        paging_identity_map((uint64_t)kernel_stack + (i * PAGE_SIZE));
    }

    // set memory map
    translate_memory_map(&memmap, &boot_info->memmap);
    boot_info->lvl5_paging = 0;

    debug("Kernel entry is located at 0x%llx\r\n", kernel_entry);
    debug("Preparing for handoff...\r\n");
    fw_prepare_handoff();

    abp_handoff(kernel_entry, boot_info, kernel_stack, 16);
}