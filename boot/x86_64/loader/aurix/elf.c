#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>
#include <loader/elf.h>

VOID *
LoaderElfLoad(VOID *FileBuffer)
{
	Elf64_Ehdr *Ehdr = (Elf64_Ehdr *)FileBuffer;
	Elf64_Phdr *Phdr = (Elf64_Phdr *)((UINT8 *)Ehdr + Ehdr->e_phoff);

	if (Ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
			 Ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
			 Ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
			 Ehdr->e_ident[EI_MAG3] != ELFMAG3) {
		EfiPrint(L"Invalid ELF header!\r\n");
		return NULL;
	}

	if (Ehdr->e_ident[EI_VERSION] != EV_CURRENT) {
		EfiPrint(L"e_ident[EI_VERSION] != EV_CURRENT\r\n");
		return NULL;
	}

	if (Ehdr->e_ident[EI_CLASS] != ELFCLASS64) {
		EfiPrint(L"e_ident[EI_CLASS] != ELFCLASS64\r\n");
		return NULL;
	}

	if (Ehdr->e_ident[EI_DATA] != ELFDATA2LSB) {
		EfiPrint(L"e_ident[EI_DATA] != ELFDATA2LSB\r\n");
		return NULL;
	}

	for (UINT16 Index = 0; Index < Ehdr->e_phnum; Index++, Phdr++) {
		if (Phdr->p_type != PT_LOAD) {
			continue;
		}

		EfiPrint(L"%u: offset=0x%x, vaddr=0x%x, paddr=0x%x\r\n", Index, Phdr->p_offset, Phdr->p_vaddr, Phdr->p_paddr);
	}

	return NULL;
}
