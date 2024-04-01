#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>

EFI_HANDLE g_ImageHandle;
EFI_SYSTEM_TABLE *g_SystemTable;

EFI_STATUS
AxBootEntryPoint(EFI_HANDLE ImageHandle,
				 EFI_SYSTEM_TABLE *SystemTable)
{
	EFI_STATUS Status;

	// we should use these global variables from now on
	g_ImageHandle = ImageHandle;
	g_SystemTable = SystemTable;

	// clear the screen
	g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
	
	// disable watchdog
	Status = g_SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
	if (EFI_ERROR(Status)) {
		EfiPrint(L"Failed to disable UEFI watchdog!\r\n");
	}

	// TEMPORARY: I've set these up only temporarily
	//			  before I make a proper config parser.
	const CHAR16 *MenuItems[] = {
		L"AurixOS",
		L"Windows",
		L"Linux"
	};

	UINTN SelectedItem = 0;
	UINTN Cols = 0;
	UINTN Rows = 0;
	g_SystemTable->ConOut->QueryMode(g_SystemTable->ConOut, g_SystemTable->ConOut->Mode->Mode, &Cols, &Rows);
	
	// main loop
	for (;;) {

		EfiPrint(L"%s v%s\r\n", BOOTLOADER_NAME, BOOTLOADER_VER_STR);
		EfiPrint(L"%s\r\n\r\n", BOOTLOADER_COPYRIGHT_STR);
		EfiPrint(L"Use UP/DOWN arrows to navigate the menu\r\n");
		EfiPrint(L"Use ENTER to boot the selected OS\r\n");
		EfiPrint(L"Use F1 to Shutdown\r\n");
		EfiPrint(L"Use F2 to Reboot\r\n\r\n\r\n");

		for (UINTN Index = 0; Index < ARRAY_SIZE(MenuItems); Index++) {
			if (Index == SelectedItem) {
				EfiPrint(L" > %s <\r\n", MenuItems[Index]);
			} else {
				EfiPrint(L"   %s\r\n", MenuItems[Index]);
			}
		}

		EFI_INPUT_KEY Key = {0,0};
		EFI_EVENT Events[1] = {g_SystemTable->ConIn->WaitForKey};
		UINTN EventIndex = 0;
		g_SystemTable->BootServices->WaitForEvent(1, Events, &EventIndex);
		
		if (EventIndex == 0) {
			g_SystemTable->ConIn->ReadKeyStroke(g_SystemTable->ConIn, &Key);
		}

		// boot selection
		if (Key.UnicodeChar == L'\r') {
			g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
			for (;;);
		}

		switch (Key.ScanCode) {
			case EFI_SCANCODE_ARROW_UP:
				if (SelectedItem <= 0) {
					SelectedItem = ARRAY_SIZE(MenuItems);
				}
				SelectedItem--;
				break;
			case EFI_SCANCODE_ARROW_DOWN:
				if (SelectedItem >= ARRAY_SIZE(MenuItems) - 1) {
					SelectedItem = 0;
					break;
				}
				SelectedItem++;
				break;
			case EFI_SCANCODE_FN1:
				g_SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
				break;
			case EFI_SCANCODE_FN2:
				g_SystemTable->RuntimeServices->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
				break;
			default:
				break;
		}

		g_SystemTable->ConOut->ClearScreen(g_SystemTable->ConOut);
	}

	return EFI_SUCCESS;
}
