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

#include <firmware/acpi.h>
#include <uefi/firmware/globals.h>
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
            return &gSystemTable->ConfigurationTable[i];
        }
    }

    // no rsdp was found
    log("ERROR: No RSDP was found!\r\n");

    return NULL;
}