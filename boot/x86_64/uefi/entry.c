/*++
Module Name:  entry.c
Project:      AurixOS

Copyright (c) 2024 Jozef Nagy

This source is subject to the MIT License.
See License.txt in the root of this repository.
All other rights reserved.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--*/

#include <efi.h>
#include <efilib.h>
#include <axboot.h>

#include <com.h>
#include <menu/bootmenu.h>
#include <print.h>

EFI_HANDLE g_ImageHandle;
EFI_SYSTEM_TABLE *g_SystemTable;

EFI_STATUS
AxBootEntry(EFI_HANDLE ImageHandle,
			EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS Status;

	g_ImageHandle = ImageHandle;
	g_SystemTable = SystemTable;

	g_SystemTable->ConOut->Reset(g_SystemTable->ConOut, EFI_FALSE);
	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);

	//
	// Set default colors (white foreground / black background)
	//
	g_SystemTable->ConOut->SetAttribute(g_SystemTable->ConOut, EFI_TEXT_ATTR(EFI_WHITE, EFI_BLACK));

	//
	// TODO: Initialize a port if debug mode is enabled
	// based on configuration file.
	//
	ComInitializeCom(COM1, 115200);

	Status = g_SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	if(EFI_ERROR(Status))
	{
		EfiPrintDebug(L"WARNING: Failed to disable UEFI watchdog\r\n");
	}

	//
	// Now we get to the best part: A boot menu.
	// This function should return ONLY if something went wrong.
	// What will happen in that case is left open for discussion,
	// so for now we just print an error message and reboot after 10 seconds.
	//
	MenuShowBootMenu();

	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
	EfiPrint(L"\r\nAn error has occured and AxBoot cannot continue working properly.\r\n");
	EfiPrint(L"The system will reboot in 10 seconds...");

    g_SystemTable->BootServices->Stall(10 * 1000000);
	g_SystemTable->RuntimeServices->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);

	return EFI_SUCCESS;
}