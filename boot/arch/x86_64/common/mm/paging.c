/*********************************************************************************/
/* Module Name:  paging.c                                                        */
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

#include <arch/cpu/cpu.h>
#include <arch/mm/paging.h>
#include <firmware/memmap.h>
#include <lib/string.h>
#include <print.h>
#include <axboot.h>

#include <lib/string.h>
#include <stdint.h>
#include <stddef.h>

struct page_table *pml4;

struct memory_map_info *g_memmap;

static void *alloc_mmap(uint64_t np)
{
	static void *next_page_address = NULL;
	static uint64_t cur_entry = 0;
	static uint64_t remaining_pages = 0;

	if (remaining_pages < np) {
		uint32_t i = cur_entry + 1;
		for (; i < g_memmap->entry_count; i++) {
			struct memory_map_entry *entry = &g_memmap->entries[i];

			if (entry->type == MemoryMapUsable && (entry->length / PAGE_SIZE) >= np) {
				cur_entry = i;
				remaining_pages = ((entry->length + PAGE_SIZE - 1) / PAGE_SIZE) - np;
				next_page_address = (void *)(entry->base + (np * PAGE_SIZE));
				return (void *)entry->base;
			}
		}

		if (i >= g_memmap->entry_count) {
			debug("Couldn't find any memory to allocate memory for.\r\n");
			return NULL;
		}
	}

	remaining_pages -= np;
	void *page = next_page_address;
	next_page_address = (void *)((uint8_t *)page + (np * PAGE_SIZE));

	return page;
}

int paging_init(struct memory_map_info *memmap)
{
	// disable write protection
	//uint64_t cr0 = read_cr0();
	//cr0 &= ~(1 << 16);
	//write_cr0(cr0);

	g_memmap = memmap;
	pml4 = alloc_mmap(1);
	memset(pml4, 0, sizeof(struct page_table));

	// identity map the memmap
	debug("Identity mapping the entire memory map...\r\n");
	for (uint32_t i = 0; i < memmap->entry_count; i++) {
		struct memory_map_entry *entry = &memmap->entries[i];

		for (uint64_t j = 0; j < (entry->length + PAGE_SIZE - 1) / PAGE_SIZE; j++) {
			paging_identity_map(entry->base + (j * PAGE_SIZE));
			paging_map(entry->base + (j * PAGE_SIZE), entry->base + 0xffff800000000000 + (j * PAGE_SIZE));
		}
	}

	return 0;
}

void paging_identity_map(uint64_t addr)
{
	paging_map(addr, addr);
}

void paging_map(uint64_t phys, uint64_t virt)
{
	const int flags = PTE_PRESENT | PTE_READ_WRITE;

	uint16_t pml4_index = (virt >> 39) & 0x1ff;
	uint16_t pdpt_index = (virt >> 30) & 0x1ff;
	uint16_t pd_index = (virt >> 21) & 0x1ff;
	uint16_t pt_index = (virt >> 12) & 0x1ff;

	if (!(pml4->entries[pml4_index] & PTE_PRESENT)) {
		void *pdpt = alloc_mmap(1);
		memset(pdpt, 0, sizeof(struct page_table));
		pml4->entries[pml4_index] = (uint64_t)pdpt | flags;
	}

	struct page_table *pdpt = (struct page_table *)(pml4->entries[pml4_index] & PHYS_PAGE_ADDR_MASK);
	if (!(pdpt->entries[pdpt_index] & PTE_PRESENT)) {
		void *pd = alloc_mmap(1);
		memset(pd, 0, sizeof(struct page_table));
		pdpt->entries[pdpt_index] = (uint64_t)pd | flags;
	}

	struct page_table *pd = (struct page_table *)(pdpt->entries[pdpt_index] & PHYS_PAGE_ADDR_MASK);
	if (!(pd->entries[pd_index] & PTE_PRESENT)) {
		void *pt = alloc_mmap(1);
		memset(pt, 0, sizeof(struct page_table));
		pd->entries[pd_index] = (uint64_t)pt | flags;
	}

	struct page_table *pt = (struct page_table *)(pd->entries[pd_index] & PHYS_PAGE_ADDR_MASK);
	if (!(pt->entries[pt_index] & PTE_PRESENT)) {
		pt->entries[pt_index] = (phys & PHYS_PAGE_ADDR_MASK) | flags;
	}
}

void paging_unmap(uint64_t virt)
{
	const int flags = PTE_PRESENT | PTE_READ_WRITE | PTE_USER;

	uint16_t pml4_index = (virt >> 39) & 0x1ff;
	uint16_t pdpt_index = (virt >> 30) & 0x1ff;
	uint16_t pd_index = (virt >> 21) & 0x1ff;
	uint16_t pt_index = (virt >> 12) & 0x1ff;

	if (!(pml4->entries[pml4_index] & PTE_PRESENT)) {
		return;
	}

	struct page_table *pdpt = (struct page_table *)(pml4->entries[pml4_index] & PHYS_PAGE_ADDR_MASK);
	if (!(pdpt->entries[pdpt_index] & PTE_PRESENT)) {
		return;
	}

	struct page_table *pd = (struct page_table *)(pdpt->entries[pdpt_index] & PHYS_PAGE_ADDR_MASK);
	if (!(pd->entries[pd_index] & PTE_PRESENT)) {
		return;
	}

	struct page_table *pt = (struct page_table *)(pd->entries[pd_index] & PHYS_PAGE_ADDR_MASK);
	if (!(pt->entries[pt_index] & PTE_PRESENT)) {
		return;
	}

	pt->entries[pt_index] = 0;

	__asm__ volatile("invlpg (%0)" :: "r"(virt));
}

uint64_t paging_get_pml4(void)
{
	return (uint64_t)pml4;
}

void *paging_allocate(size_t np)
{
	return alloc_mmap(np);
}