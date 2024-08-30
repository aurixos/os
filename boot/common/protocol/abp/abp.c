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
#include <lib/string.h>
#include <print.h>
#include <axboot.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef void (*entryp)(struct abp_boot_info *);

void abp_load(void *kernel)
{
    bool higher_half = false;
    struct abp_boot_info boot_info = {0};
    entryp kernel_entry;

    // set up basic boot information
    strcpy(boot_info.bootloader_name, BOOTLOADER_NAME_STR);
    strcpy(boot_info.bootloader_version, BOOTLOADER_VERSION_STR);
    strcpy(boot_info.protocol_version, AXBOOT_PROTOCOL_VERSION_STR);

    // get kernel entry point
    kernel_entry = (entryp)elf_load(kernel, &higher_half);
    if (kernel_entry == NULL) {
        return;
    }

    // get ACPI and SMBIOS info
    boot_info.acpi.rsdp = fw_get_acpi_rsdp();
    if (boot_info.acpi.rsdp != NULL) {
        boot_info.acpi.is_valid = 1;
    }

    boot_info.smbios.entry_point = fw_get_smbios_entry_point();
    if (boot_info.smbios.entry_point != NULL) {
        boot_info.smbios.is_valid = 1;
    }

    // get framebuffer info
    //boot_info.framebuffer_cnt = fb_get_framebuffer_count();
    //for (int i = 0; i < boot_info.framebuffer_cnt; i++) {
    //    boot_info.framebuffer[i] = fb_get_framebuffer(i);
    //}

    // get memory map;
    // on UEFI, this also calls BS->ExitBootServices()
    //boot_info.memmap = fw_get_memmap(&boot_info.memmap_entcnt);

    // disable interrupts and hope for the best.
    cpu_disable_interrupts();

    debug("Jumping to kernel at %x...\r\n", (uint64_t)kernel_entry);

    kernel_entry(&boot_info);
}