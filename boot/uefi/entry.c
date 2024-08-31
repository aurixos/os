/*********************************************************************************/
/* Module Name:  entry.c                                                         */
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

#include <efi.h>
#include <efilib.h>

#include <firmware/firmware.h>
#include <firmware/fb.h>
#include <menu/menu.h>
#include <loader/loader.h>
#include <loader/elf.h>
#include <print.h>

#include <stddef.h>

EFI_STATUS uefi_entry(EFI_HANDLE ImageHandle,
                       EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;

    gImageHandle = ImageHandle;
    gSystemTable = SystemTable;

    // clear the screen
    gSystemTable->ConOut->ClearScreen(gSystemTable->ConOut);

    // disable UEFI watchdog
    Status = gSystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    if (EFI_ERROR(Status)) {
        debug("Couldn't disable UEFI watchdog!\n");
    }

    firmware_init();

    if (fw_initialize_fb() != 0) {
        debug("No valid framebuffer was found!\r\n");
    }

    //menu_main();

    loader_load(ProtocolAbp, "\\System\\axkrnl");

    debug("Tried to return from main()! Halting...\r\n");
    while(1);

    return EFI_SUCCESS;
}