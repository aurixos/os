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

int elf_validate_header(Elf64Hdr *header)
{
	if (header == NULL) {
		log("ERROR: elf_validate_header() called with NULL argument!\r\n");
		return -1;
	}

	if (header->ident[EI_MAG0] != ELFMAG0 ||
			header->ident[EI_MAG1] != ELFMAG1 ||
			header->ident[EI_MAG2] != ELFMAG2 ||
			header->ident[EI_MAG3] != ELFMAG3) {
		return -1;
	}

	// TODO: Revise this
	if (header->type != ET_EXEC ||
			header->machine != EM_X86_64 ||
			header->version != EV_CURRENT) {
		return -1;
	}

	return 0;
}

ElfExecHandle *elf_load(void *kernel)
{
	ElfExecHandle *handle = malloc(sizeof(ElfExecHandle));
	Elf64Hdr *header = (Elf64Hdr *)kernel;

	if (elf_validate_header(header) != 0) {
		log("ERROR: Invalid ELF header!\r\n");
		return NULL;
	}

	if (header->phnum <= 0) {
		log("ERROR: No loadable ELF segments found.\r\n");
		return NULL;
	}

	// TODO: print some debug information about the ELF file

	Elf64Phdr *phdrs = (Elf64Phdr *)(kernel + header->phoff);
	for (uint16_t i = 0; i < header->phnum; i++) {
		Elf64Phdr *phdr = (Elf64Phdr *)phdrs;
		if (phdr->type == PT_LOAD) {
			void *file_segment = (void *)((uint64_t)kernel + phdr->offset);
			void *memory_segment = (void *)phdr->vaddr;

			memcpy(memory_segment, file_segment, phdr->filesz);

			uint8_t *extra_zeroes = (uint8_t *)memory_segment + phdr->filesz;
			uint64_t extra_zeroes_count = phdr->memsz - phdr->filesz;

			if (extra_zeroes_count > 0) {
				memset(extra_zeroes, 0x00, extra_zeroes_count);
			}
		}
		phdrs = (Elf64Phdr *)(phdrs + header->phentsize);
	}

	handle->entry_point = (void *)header->entry;

	return handle;
}