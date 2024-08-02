/*********************************************************************************/
/* Module Name:  elf.h                                                        */
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

#ifndef _LOADER_ELF_ELF_H
#define _LOADER_ELF_ELF_H

#define EI_NIDENT 16
#define EI_MAG0 0
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3
#define EI_CLASS 4
#define EI_DATA 5
#define EI_VERSION 6

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define ELFCLASS64 2
#define ELFDATA2LSB 1
#define EV_CURRENT 1

#define ET_EXEC 2
#define EM_X86_64 62

#define PT_LOAD 1
#define PT_PHDR 6

typedef unsigned short elf_half;
typedef unsigned int elf_word;
typedef unsigned long long elf_xword;
typedef unsigned long long elf_addr;
typedef unsigned long long elf_off;

typedef struct
{
    unsigned char ident[EI_NIDENT];
    elf_half type;
    elf_half machine;
    elf_word version;
    elf_addr entry;
    elf_off phoff;
    elf_off shoff;
    elf_word flags;
    elf_half ehsize;
    elf_half phentsize;
    elf_half phnum;
    elf_half shentsize;
    elf_half shnum;
    elf_half shstrndx;
} __attribute__((packed)) Elf64Hdr;

typedef struct
{
    elf_word type;
    elf_word flags;
    elf_off offset;
    elf_addr vaddr;
    elf_addr paddr;
    elf_xword filesz;
    elf_xword memsz;
    elf_xword align;
} __attribute__((packed)) Elf64Phdr;

typedef struct {
    void *entry_point;
} ElfExecHandle;

ElfExecHandle *elf_load(void *kernel);

#endif /* _LOADER_ELF_ELF_H */
