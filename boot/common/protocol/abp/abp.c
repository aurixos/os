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

#include <protocol/abp.h>
#include <loader/elf.h>
#include <firmware/acpi.h>
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
    boot_info.bootloader_name = BOOTLOADER_NAME_STR;
    boot_info.bootloader_name = BOOTLOADER_VERSION_STR;
    boot_info.protocol_version = AXBOOT_PROTOCOL_VERSION_STR;

    // get kernel entry point
    kernel_entry = (entryp)elf_load(kernel, &higher_half);
    if (kernel_entry == NULL) {
        return;
    }

    // get ACPI info
    boot_info.acpi.rsdp = fw_get_acpi_rsdp();
    if (boot_info.acpi.rsdp == NULL) {
        return;
    }

    kernel_entry(&boot_info);
}