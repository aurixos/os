#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <config.h>
#include <print.h>
#include <file.h>

#include <loader/aurix.h>
#include <loader/elf.h>

VOID
LoaderAurixBoot(struct BootEntry *Entry)
{
	EFI_FILE_PROTOCOL *KernelFile;
	EFI_STATUS Status;
	UINTN KernelSize = 0;
	UINT64 KernelEntryAddr = 0;

	KernelFile = FileOpen(Entry->KernelPath, &KernelSize);

	Status = LoaderElfLoad(KernelFile, &KernelEntryAddr);
	if (EFI_ERROR(Status)) {
		EfiPrint(L"An error occured while loading AurixOS!\r\n");
		for (;;);
	}
	EfiPrint(L"Loaded AurixOS\r\n");

	VOID (__attribute__((sysv_abi)) *AurixKernelEntry)(VOID) = ((VOID (__attribute__((sysv_abi)) *)(VOID))KernelEntryAddr);
	AurixKernelEntry();

	for (;;);
}
