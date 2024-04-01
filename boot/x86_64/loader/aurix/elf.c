#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>
#include <loader/elf.h>

VOID *
LoaderElfParse(VOID *FileBuffer)
{
	ElfEHeader64 *EHdr = (ElfEHeader64 *)FileBuffer;

	EfiPrint(L"Type: %u\r\nMachine: 0x%x\r\nEntry: 0x%x\r\n", EHdr->e_type, EHdr->e_machine, EHdr->e_entry);

	return NULL;
}
