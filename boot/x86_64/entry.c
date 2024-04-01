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

	for (;;);

	return EFI_SUCCESS;
}
