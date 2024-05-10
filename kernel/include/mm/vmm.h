#ifndef _MM_VMM_H
#define _MM_VMM_H

#include <arch/mm.h>

#include <stdint.h>

void vmm_init(void);

void vmm_map_range(page_table_t *page_table, uintptr_t phys_start, uintptr_t phys_end, uintptr_t offset, uint64_t flags, uint64_t type);
void vmm_unmap_range(page_table_t *page_table, uintptr_t virt, size_t npages);

#endif /* _MM_VMM_H */
