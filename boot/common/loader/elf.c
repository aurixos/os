/*********************************************************************************/
/* Module Name:  elf.c                                                           */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024-2025 Jozef Nagy                                            */
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

#include <loader/elf.h>
#include <mm/vmm.h>
#include <mm/mman.h>
#include <lib/string.h>
#include <lib/align.h>
#include <print.h>
#include <stdint.h>

/* https://github.com/KevinAlavik/nekonix/blob/main/kernel/src/proc/elf.c */
/* Thanks, Kevin <3 */

uint64_t elf_load(char *data, uintptr_t *pagemap)
{
    struct elf_header *header = (struct elf_header *)data;

    if (header->e_magic != ELF_MAGIC) {
        debug("Invalid ELF magic: 0x%x", header->e_magic);
        return 0;
    }

    if (header->e_class != 2) {
        debug("Unsupported ELF class: %u", header->e_class);
        return 0;
    }

    struct elf_program_header *ph = (struct elf_program_header *)(data + header->e_phoff);

    for (uint16_t i = 0; i < header->e_phnum; i++) {
        if (ph[i].p_type != PT_LOAD)
            continue;

        uint64_t vaddr_start = ALIGN_DOWN(ph[i].p_vaddr, PAGE_SIZE);
        uint64_t vaddr_end = ALIGN_UP(ph[i].p_vaddr + ph[i].p_memsz, PAGE_SIZE);
        uint64_t offset = ph[i].p_offset;

        uint64_t flags = VMM_PRESENT;
        if (ph[i].p_flags & PF_W)
            flags |= VMM_WRITABLE;
        if (!(ph[i].p_flags & PF_X))
            flags |= VMM_NX;

        for (uint64_t addr = vaddr_start; addr < vaddr_end; addr += PAGE_SIZE) {
            uint64_t phys = (uint64_t)mem_alloc(PAGE_SIZE);
            if (!phys) {
                debug("Out of physical memory");
                return 0;
            }

            map_page(pagemap, addr, phys, flags);

            uint64_t file_offset = offset + (addr - vaddr_start);
            if (file_offset < offset + ph[i].p_filesz) {
                uint64_t to_copy = PAGE_SIZE;
                if (file_offset + PAGE_SIZE > offset + ph[i].p_filesz)
                    to_copy = offset + ph[i].p_filesz - file_offset;

                memcpy((void *)phys, data + file_offset, to_copy);
            } else {
                memset((void *)phys, 0, PAGE_SIZE);
            }
        }
    }

    debug("ELF loaded successfully, entry: 0x%lx", header->e_entry);
    return header->e_entry;
}
