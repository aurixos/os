/*********************************************************************************/
/* Module Name:  acpi.c                                                          */
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

#include <firmware/hwmgmnt.h>
#include <firmware/firmware.h>
#include <lib/string.h>
#include <print.h>

#include <efi.h>
#include <efilib.h>

#include <stddef.h>

void *fw_get_acpi_rsdp(void)
{
    void *cfgtbl = gSystemTable->ConfigurationTable->VendorTable;
    EFI_GUID acpi10 = EFI_ACPI_10_TABLE_GUID;
    EFI_GUID acpi20 = EFI_ACPI_20_TABLE_GUID;

    for (EFI_UINTN i = 0; i < gSystemTable->NumberOfTableEntries; i++) {
        if (!memcmp(&gSystemTable->ConfigurationTable[i].VendorGuid, &acpi10, sizeof(EFI_GUID)) ||
            !memcmp(&gSystemTable->ConfigurationTable[i].VendorGuid, &acpi20, sizeof(EFI_GUID))) {
            // let's just do one more check to be sure
            void *ptr = gSystemTable->ConfigurationTable[i].VendorTable;
            if (!memcmp(ptr, "RSD PTR ", 8)) {
                debug("Found RSDP at 0x%lx\r\n", ptr);
                return ptr;
            }
        }
    }

    // no rsdp was found
    debug("ERROR: No RSDP was found!\r\n");

    return NULL;
}

void *fw_get_smbios_entry_point(void)
{
    void *cfgtbl = gSystemTable->ConfigurationTable->VendorTable;
    EFI_GUID smbios2 = SMBIOS_TABLE_GUID;
    EFI_GUID smbios3 = SMBIOS3_TABLE_GUID;

    for (EFI_UINTN i = 0; i < gSystemTable->NumberOfTableEntries; i++) {
        if (!memcmp(&gSystemTable->ConfigurationTable[i].VendorGuid, &smbios2, sizeof(EFI_GUID)) ||
            !memcmp(&gSystemTable->ConfigurationTable[i].VendorGuid, &smbios3, sizeof(EFI_GUID))) {
            // let's just do one more check to be sure
            void *ptr = gSystemTable->ConfigurationTable[i].VendorTable;
            if (!memcmp(ptr, "_SM_", 5) ||
                !memcmp(ptr, "_SM3_", 5)) {
                debug("Found SMBIOS entry point at 0x%lx\r\n", ptr);
                return ptr;
            }
        }
    }

    // no entry point was found
    debug("ERROR: No SMBIOS Entry Point was found!\r\n");

    return NULL;
}