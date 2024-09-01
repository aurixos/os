/*********************************************************************************/
/* Module Name:  paging.h                                                        */
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

#ifndef _MM_PAGING_H
#define _MM_PAGING_H

#include <firmware/memmap.h>

#include <stdint.h>

#define PAGE_SIZE 0x1000
#define PHYS_PAGE_ADDR_MASK 0x000FFFFFFFFFF000

struct page_table {
	uint64_t entries[512];
};

// pte flags
#define PTE_PRESENT (1)
#define PTE_READ_WRITE (1 << 1)
#define PTE_USER (1 << 2)
#define PTE_WRITE_THROUGH (1 << 3)
#define PTE_CACHE_DISABLE (1 << 4)
#define PTE_ACCESSED (1 << 5)
#define PTE_DIRTY (1 << 6)
#define PTE_PAT (1 << 7)
#define PTE_GLOBAL (1 << 8)

int paging_init(struct memory_map_info *memmap);

void paging_identity_map(uint64_t addr);
void paging_map(uint64_t phys, uint64_t virt);
void paging_unmap(uint64_t virt);

void *paging_allocate(size_t np);

#endif /* _MM_PAGING_H */