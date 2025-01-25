/*********************************************************************************/
/* Module Name:  entry.c                                                         */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024-2025 Jozef Nagy                                            */
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

#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <mm/mman.h>
#include <lib/string.h>
#include <print.h>

#include <stddef.h>

EFI_HANDLE gImageHandle;
EFI_SYSTEM_TABLE *gSystemTable;
EFI_BOOT_SERVICES *gBootServices;

EFI_STATUS uefi_entry(EFI_HANDLE ImageHandle,
                       EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;

    gImageHandle = ImageHandle;
    gSystemTable = SystemTable;
    gBootServices = SystemTable->BootServices;

    // clear the screen
    gSystemTable->ConOut->ClearScreen(gSystemTable->ConOut);

    // disable UEFI watchdog
    Status = gSystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    if (EFI_ERROR(Status)) {
        debug("Couldn't disable UEFI watchdog: %s (%x)\n", efi_status_to_str(Status), Status);
    }

    axboot_init();
    UNREACHABLE();
}