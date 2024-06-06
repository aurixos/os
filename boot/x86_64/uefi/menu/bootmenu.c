/*++
Module Name:  bootmenu.c
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

#include <axboot.h>
#include <efi.h>
#include <efilib.h>

#include <print.h>
#include <menu/bootmenu.h>
#include <input/kbd.h>

typedef struct _BOOT_ENTRY
{
	CHAR16 *Name;
	CHAR16 *KernelPath;
} BOOT_ENTRY, *PBOOT_ENTRY;

VOID
MenuShowBootMenu()
{
	BOOLEAN ShouldRun = TRUE;
	UINT SelectedEntry = 0;
	UINT MaximumEntries = 0;
	BOOT_ENTRY BootEntries[3] = {
		{
			L"Test Entry #1",
			L"",
		},
		{
			L"Test Entry #2",
			L"",
		},
		{
			L"Test Entry #3",
			L"",
		},
	};

	MaximumEntries = ARRAY_SIZE(BootEntries);

	while(ShouldRun)
	{
		//
		// Get info about the screen
		//
		UINTN Cols = 0;
		UINTN Rows = 0;
		g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
		g_SystemTable->ConOut->QueryMode(g_SystemTable->ConOut, g_SystemTable->ConOut->Mode->Mode, &Cols, &Rows);

		//
		// Show some nice info
		//
		EfiPrint(L"AxBoot v%s-%s %s\r\n\r\n", AXBOOT_VERSION_STR, AURIXOS_CONFIGURATION, AXBOOT_COPYRIGHT_STR);

		EfiPrint(L"Press F1 to Shutdown\r\n");
		EfiPrint(L"Press F2 to Reboot\r\n");
		EfiPrint(L"Use ↑/↓ to navigate the menu\r\n");
		EfiPrint(L"Press ENTER to boot selected OS\r\n");
		EfiPrint(L"Press S to spawn a shell\r\n\r\n\r\n");

		for(UINTN EntryIndex = 0; EntryIndex < MaximumEntries; EntryIndex++)
		{
			if(EntryIndex == SelectedEntry)
			{
				EfiPrint(L" > %s <\r\n", BootEntries[EntryIndex].Name);
			}
			else
			{
				EfiPrint(L"   %s\r\n", BootEntries[EntryIndex].Name);
			}
		}

		EFI_INPUT_KEY Key = InputGetKey();
		switch(Key.ScanCode)
		{
			//
			// F1 - Shutdown
			//
			case EFI_SCANCODE_FN1:
				g_SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, 0, 0, NULL);
				break;
			//
			// F2 - Warm Reboot
			//
			case EFI_SCANCODE_FN2:
				g_SystemTable->RuntimeServices->ResetSystem(EfiResetWarm, 0, 0, NULL);
				break;
			//
			// Arrow Up - Scroll up
			//
			case EFI_SCANCODE_ARROW_UP:
				if(SelectedEntry <= 0)
				{
					SelectedEntry = MaximumEntries - 1;
				}
				else
				{
					SelectedEntry--;
				}
				EfiPrintDebug(L"SelectedEntry: %d", SelectedEntry);
				break;
			//
			// Arrow Down - Scroll down
			//
			case EFI_SCANCODE_ARROW_DOWN:
				if(SelectedEntry + 1 >= MaximumEntries)
				{
					SelectedEntry = 0;
				}
				else
				{
					SelectedEntry++;
				}
				EfiPrintDebug(L"SelectedEntry: %d", SelectedEntry);
				break;
			default:
				//
				// Enter - boot current selection
				//
				if(Key.UnicodeChar == L'\r')
				{
					g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
					EfiPrintDebug(L"Booting \"%s\"...\r\n", BootEntries[SelectedEntry].Name);
					EfiPrint(L"Booting \"%s\"...\r\n", BootEntries[SelectedEntry].Name);
					while(1);
				}
				//
				// S - Run shell
				//
				else if(Key.UnicodeChar == L's' || Key.UnicodeChar == L's')
				{
					g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
					EfiPrintDebug(L"Running shell...\r\n");
					EfiPrint(L">");
					while(1);
				}
				break;
		}

		//
		// TODO: Get rid of this
		//
		//while(1);
	}
}