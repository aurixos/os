#include <axboot.h>
#include <config.h>
#include <print.h>
#include <file.h>

#include <loader/aurix.h>
#include <loader/elf.h>

VOID
LoaderAurixBoot(struct BootEntry *Entry)
{
	UINTN KernelSize = 0;
	VOID *Kernel = FileRead(Entry->KernelPath, &KernelSize);

	LoaderElfParse(Kernel);

	g_SystemTable->BootServices->FreePool(Kernel);
	EfiPrint(L"Loaded AurixOS\r\n");
	for (;;);
}
