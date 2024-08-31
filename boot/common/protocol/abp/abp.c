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

#define ABP_MEMORY_RESERVED 0xf0
#define ABP_MEMORY_USABLE 0xf1
#define ABP_MEMORY_BOOTLOADER_RECLAIMABLE 0xf2
#define ABP_MEMORY_MMIO 0xf3
#define ABP_MEMORY_ACPI_NVS 0xf4
#define ABP_MEMORY_ACPI_RECLAIMABLE 0xf5
#define ABP_MEMORY_KERNEL 0xf7
#define ABP_MEMORY_NOT_USABLE 0xff

typedef void (*entryp)(struct abp_boot_info *);

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

void abp_load(void *kernel)
{
    bool higher_half = false;
    struct abp_boot_info *boot_info = malloc(sizeof(struct abp_boot_info));
    entryp kernel_entry;

    // set up basic boot information
    boot_info->bootloader_name = malloc(strlen(BOOTLOADER_NAME_STR));
    boot_info->bootloader_version = malloc(strlen(BOOTLOADER_VERSION_STR));
    boot_info->protocol_version = malloc(strlen(AXBOOT_PROTOCOL_VERSION_STR));
    strcpy(boot_info->bootloader_name, BOOTLOADER_NAME_STR);
    strcpy(boot_info->bootloader_version, BOOTLOADER_VERSION_STR);
    strcpy(boot_info->protocol_version, AXBOOT_PROTOCOL_VERSION_STR);

    // get kernel entry point
    kernel_entry = (entryp)elf_load(kernel, &higher_half);
    if (kernel_entry == NULL) {
        return;
    }

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

    debug("Framebuffer info:\r\n");
    debug("- Address: 0x%lx\r\n", boot_info->framebuffer.addr);
    debug("- Width: 0x%u\r\n", boot_info->framebuffer.width);
    debug("- Height: 0x%u\r\n", boot_info->framebuffer.height);
    debug("- Bits per pixel: %u\r\n", boot_info->framebuffer.bpp);
    debug("- Pixel Format: %s\r\n", boot_info->framebuffer.pixel_format == AbpFramebufferRgba ? "RGBA" : "BGRA");

    // get memory map
    struct memory_map_info memmap = {0};
    fw_get_memory_map(&memmap);
    memmap_dump(&memmap);
    translate_memory_map(&memmap, &boot_info->memmap);
    boot_info->lvl5_paging = 0;

    // LET'S FUCKING GOOOOOO
    debug("Preparing for handoff...\r\n");
    fw_prepare_handoff();
    cpu_disable_interrupts();

    debug("Jumping to kernel at %x...\r\n", (uint64_t)kernel_entry);

    kernel_entry(boot_info);
}