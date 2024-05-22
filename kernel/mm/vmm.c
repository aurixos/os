#include <mm/mm.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

extern uint64_t *kernel_pt;

void vmm_map_range(page_map_t *page_table, uintptr_t phys_start, uintptr_t phys_end, uintptr_t offset, uint64_t flags)
{
	if (page_table == NULL) {
		page_table = kernel_pt;
	}

	for (size_t i = ALIGN_DOWN(phys_start, PAGE_SIZE); i < ALIGN_UP(phys_end, PAGE_SIZE); i += PAGE_SIZE) {
		vmm_map(page_table, i, i + offset, flags);
	}
}

void vmm_unmap_range(page_map_t *page_table, uintptr_t virt, size_t npages)
{
	if (page_table == NULL) {
		page_table = kernel_pt;
	}

	for (size_t i = 0; i < npages * PAGE_SIZE; i += PAGE_SIZE) {
		vmm_unmap(page_table, virt + i);
	}
}
