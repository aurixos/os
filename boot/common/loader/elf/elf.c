/*********************************************************************************/
/* Module Name:  elf.c                                                           */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024 Jozef Nagy                                                 */
/*                                                                               */
/* This source is subject to the MIT License.                                    */
/* See License.txt in the root of this repository.                               */
/* All other rights reserved.                                                    */
/*                                                                               */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE.                                                                     */
/*********************************************************************************/

#include <firmware/file.h>
#include <loader/elf.h>
#include <lib/string.h>
#include <print.h>

#include <stddef.h>

int elf_validate_header(Elf32_Ehdr *header)
{
	if (header == NULL) {
		log("ERROR: elf_validate_header() called with NULL argument!\r\n");
		return -1;
	}

	if (header->e_ident[EI_MAG0] != ELFMAG0 ||
			header->e_ident[EI_MAG1] != ELFMAG1 ||
			header->e_ident[EI_MAG2] != ELFMAG2 ||
			header->e_ident[EI_MAG3] != ELFMAG3) {
		log("ERROR: Invalid ELF magic value!\r\n");
		return -1;
	}

	// TODO: Revise this
	if (header->e_type != ET_EXEC) {
		log("ERROR: ELF file is not an executable!\r\n");
		return -1;
	}

	if (header->e_version != EV_CURRENT) {
		log("ERROR: ELF version is not EV_CURRENT!\r\n");
		return -1;
	}

	return 0;
}

void *elf_load(void *kernel)
{
	Elf32_Ehdr *header32 = (Elf32_Ehdr *)kernel;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)kernel;

	if (elf_validate_header(header32) != 0) {
		log("ERROR: Invalid ELF header!\r\n");
		return NULL;
	}

	// TODO: print some debug information about the ELF file

	if (header32->e_machine == EM_386 ||
		header32->e_machine == EM_ARM ||
		header32->e_machine == EM_PPC) {
		if (header32->e_phnum <= 0) {
			log("ERROR: No loadable ELF segments found.\r\n");
			return NULL;
		}

		Elf32_Phdr *phdrs32 = (Elf32_Phdr *)(kernel + header32->e_phoff);
		for (uint16_t i = 0; i < header32->e_phnum; i++) {
			Elf32_Phdr *phdr32 = (Elf32_Phdr *)phdrs32;
			if (phdr32->p_type == PT_LOAD) {
				void *file_segment = (void *)((uintptr_t)kernel + phdr32->p_offset);
				void *memory_segment = (void *)(uintptr_t)phdr32->p_vaddr;

				memcpy(memory_segment, file_segment, phdr32->p_filesz);

				uint8_t *extra_zeroes = (uint8_t *)memory_segment + phdr32->p_filesz;
				uint64_t extra_zeroes_count = phdr32->p_memsz - phdr32->p_filesz;

				if (extra_zeroes_count > 0) {
					memset(extra_zeroes, 0x00, extra_zeroes_count);
				}
			}

			phdrs32 = (Elf32_Phdr *)((uint8_t*)phdrs32 + header32->e_phentsize);
		}
	} else {
		if (header64->e_phnum <= 0) {
			log("ERROR: No loadable ELF segments found.\r\n");
			return NULL;
		}

		Elf64_Phdr *phdrs64 = (Elf64_Phdr *)(kernel + header64->e_phoff);
		for (uint16_t i = 0; i < header64->e_phnum; i++) {
			Elf64_Phdr *phdr64 = (Elf64_Phdr *)phdrs64;
			if (phdr64->p_type == PT_LOAD) {
				void *file_segment = (void *)((uintptr_t)kernel + phdr64->p_offset);
				void *memory_segment = (void *)(uintptr_t)phdr64->p_vaddr;

				memcpy(memory_segment, file_segment, phdr64->p_filesz);

				uint8_t *extra_zeroes = (uint8_t *)memory_segment + phdr64->p_filesz;
				uint64_t extra_zeroes_count = phdr64->p_memsz - phdr64->p_filesz;

				if (extra_zeroes_count > 0) {
					memset(extra_zeroes, 0x00, extra_zeroes_count);
				}
			}

			phdrs64 = (Elf64_Phdr *)((uint8_t *)phdrs64 + header64->e_phentsize);
		}
	}

	return (void *)header64->e_entry;
}