#ifndef __LOADER_ELF_H
#define __LOADER_ELF_H

#include <efi_types.h>

typedef enum {
	ET_EXEC = 0x2,
	ET_DYN = 0x3,
} ELF_EHEADER_TYPE;

typedef enum {
	PT_NULL = 0x0,
	PT_LOAD = 0x1,
} ELF_PHEADER_TYPE;

typedef struct {
	struct {
		UINT8 ei_mag0;
		UINT8 ei_mag1;
		UINT8 ei_mag2;
		UINT8 ei_mag3;
		UINT8 ei_class;
		UINT8 ei_data;
		UINT8 ei_version;
		UINT8 ei_osabi;
		UINT8 ei_abiversion;
		UINT8 ei_pad[7];
	} e_ident;
	UINT16 e_type;
	UINT16 e_machine;
	UINT32 e_version;
	UINT64 e_entry;
	UINT64 e_phoff;
	UINT64 e_shoff;
	UINT32 e_flags;
	UINT16 e_ehsize;
	UINT16 e_phentsize;
	UINT16 e_phnum;
	UINT16 e_shentsize;
	UINT16 e_shnum;
	UINT16 e_shstrndx;
} __attribute__((packed)) ElfEHeader64;

typedef struct {
	UINT32 p_type;
	UINT32 p_flags;
	UINT64 p_offset;
	UINT64 p_vaddr;
	UINT64 p_paddr;
	UINT64 p_filesz;
	UINT64 p_memsz;
	UINT64 p_align;
} __attribute__((packed)) ElfPHeader64;

VOID *
LoaderElfParse(VOID *FileBuffer);

#endif /* __LOADER_ELF_H */
