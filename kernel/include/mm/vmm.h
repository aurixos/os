#ifndef _MM_VMM_H
#define _MM_VMM_H

#include <arch/mm.h>

#include <stdint.h>

void vmm_init(void);

typedef uint64_t page_map_t;

void vmm_map_range(page_map_t *page_table, uintptr_t phys_start, uintptr_t phys_end, uintptr_t offset, uint64_t flags);
void vmm_unmap_range(page_map_t *page_table, uintptr_t virt, size_t npages);

#endif /* _MM_VMM_H */
