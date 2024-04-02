#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>
#include <file.h>
#include <loader/elf.h>

EFI_STATUS
LoaderElfLoadHeader(EFI_FILE_PROTOCOL *File, Elf64_Ehdr *Header)
{
	UINTN ReadSize = sizeof(Elf64_Ehdr);
	return File->Read(File, &ReadSize, (VOID *)Header);
}

EFI_STATUS
LoaderElfVerifyHeader(Elf64_Ehdr *Header)
{
	if (Header->e_ident[EI_MAG0] != ELFMAG0 ||
		Header->e_ident[EI_MAG1] != ELFMAG1 ||
		Header->e_ident[EI_MAG2] != ELFMAG2 ||
		Header->e_ident[EI_MAG3] != ELFMAG3 ||
		Header->e_ident[EI_DATA] != ELFDATA2LSB ||
		Header->e_ident[EI_CLASS] != ELFCLASS64 ||
		Header->e_type != ET_EXEC ||
		Header->e_machine != EM_X86_64 ||
		Header->e_version != EV_CURRENT)
	{
		return EFI_INVALID_PARAMETER;
	}
	return EFI_SUCCESS;
}

EFI_STATUS
LoaderElfLoadProgramHeaders(EFI_FILE_PROTOCOL *File, Elf64_Ehdr *Ehdr, Elf64_Phdr *Phdrs)
{
	EFI_STATUS Status;
	UINTN PhdrSize = Ehdr->e_phnum * Ehdr->e_phentsize;

	Status = File->SetPosition(File, Ehdr->e_phoff);
	if (EFI_ERROR(Status)) {
		return Status;
	}

	Status = g_SystemTable->BootServices->AllocatePool(EfiLoaderData, PhdrSize, (VOID **)&Phdrs);
	if (EFI_ERROR(Status)) {
		return Status;
	}

	Status = File->Read(File, &PhdrSize, Phdrs);
	if (EFI_ERROR(Status)) {
		return Status;
	}

	for (Elf64_Phdr *Phdr = Phdrs; (CHAR *)Phdr < (CHAR *)Phdrs + PhdrSize; Phdr = (Elf64_Phdr *)((CHAR *)Phdr + Ehdr->e_phentsize)) {
		if (Phdr->p_type == PT_LOAD) {
			INT PageCount = (Phdr->p_memsz + 0x1000 - 1) / 0x1000;
			UINT64 Segment = Phdr->p_paddr - 0xffffffff80000000;
			UINTN ProgramSize = Phdr->p_filesz;

			Status = g_SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, PageCount, &Segment);
			if (EFI_ERROR(Status)) {
				return Status;
			}

			Status = File->SetPosition(File, Phdr->p_offset);
			if (EFI_ERROR(Status)) {
				return Status;
			}

			Status = File->Read(File, &ProgramSize, (VOID *)Segment);
			if (EFI_ERROR(Status)) {
				return Status;
			}
		}
	}

	return EFI_SUCCESS;
}

EFI_STATUS
LoaderElfLoad(EFI_FILE_PROTOCOL *File, UINT64 *EntryPoint)
{
	EFI_STATUS Status;
	Elf64_Ehdr Ehdr;
	Elf64_Phdr *Phdr = NULL;

	if (File == NULL) return EFI_INVALID_PARAMETER;
	if (EntryPoint == NULL) return EFI_INVALID_PARAMETER;

	Status = LoaderElfLoadHeader(File, &Ehdr);
	if (EFI_ERROR(Status)) {
		return Status;
	}

	Status = LoaderElfVerifyHeader(&Ehdr);
	if (EFI_ERROR(Status)) {
		return EFI_INVALID_PARAMETER;
	}

	Status = LoaderElfLoadProgramHeaders(File, &Ehdr, Phdr);
	if (EFI_ERROR(Status)) {
		return EFI_LOAD_ERROR;
	}

	EntryPoint = (VOID *)Ehdr.e_entry;

	FileClose(File);

	return EFI_SUCCESS;
}
