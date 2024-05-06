#include <mm/mm.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

void vmm_map_range(page_table_t *page_table, uintptr_t phys, uintptr_t virt, size_t npages, uint64_t flags, uint64_t type)
{
	for (size_t i = 0; i < npages * PAGE_SIZE; i += PAGE_SIZE) {
		vmm_map(page_table, phys + i, virt + i, flags, type);
	}
}

void vmm_unmap_range(page_table_t *page_table, uintptr_t virt, size_t npages)
{
	for (size_t i = 0; i < npages * PAGE_SIZE; i += PAGE_SIZE) {
		vmm_unmap(page_table, virt + i);
	}
}
