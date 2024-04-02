#ifndef __LOADER_ELF_H
#define __LOADER_ELF_H

#include <efi_types.h>

#define	EI_MAG0 0
#define	EI_MAG1 1
#define	EI_MAG2 2
#define	EI_MAG3 3
#define	EI_CLASS 4
#define	EI_DATA 5
#define	EI_VERSION 6
#define EI_NIDENT 16

#define	ELFMAG0 0x7f
#define	ELFMAG1 'E'
#define	ELFMAG2 'L'
#define	ELFMAG3 'F'

#define	EV_CURRENT 1
#define	ELFCLASS64 2
#define	ELFDATA2LSB	1

#define ET_EXEC 2

#define EM_X86_64 62

#define	PT_NULL 0
#define	PT_LOAD 1
#define	PT_DYNAMIC 2
#define	PT_INTERP 3
#define	PT_NOTE 4
#define	PT_SHLIB 5
#define	PT_PHDR 6
#define	PT_TLS 7;

typedef struct {
    unsigned char e_ident[EI_NIDENT];
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
} Elf64_Ehdr;

typedef struct {
    UINT32 sh_name;
    UINT32 sh_type;
    UINT64 sh_flags;
    UINT64 sh_addr;
    UINT64 sh_offset;
    UINT64 sh_size;
    UINT32 sh_link;
    UINT32 sh_info;
    UINT64 sh_addralign;
    UINT64 sh_entsize;
} Elf64_Shdr;

typedef struct {
    UINT32 p_type;
    UINT32 p_flags;
    UINT64 p_offset;
    UINT64 p_vaddr;
    UINT64 p_paddr;
    UINT64 p_filesz;
    UINT64 p_memsz;
    UINT64 p_align;
} Elf64_Phdr;

EFI_STATUS
LoaderElfLoadHeader(EFI_FILE_PROTOCOL *File, Elf64_Ehdr *Header);

EFI_STATUS
LoaderElfVerifyHeader(Elf64_Ehdr *Header);

EFI_STATUS
LoaderElfLoadProgramHeaders(EFI_FILE_PROTOCOL *File, Elf64_Ehdr *Ehdr, Elf64_Phdr *Phdr);

EFI_STATUS
LoaderElfLoad(EFI_FILE_PROTOCOL *File, UINT64 *EntryPoint);

#endif /* __LOADER_ELF_H */
