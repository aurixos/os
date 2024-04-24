#ifndef _MM_PMM_H
#define _MM_PMM_H

#include <data/bmap.h>
#include <mm/mm.h>

struct pmm_info {
	bitmap_t bitmap;
	size_t mem_top;
	size_t used_pages;
};

void pmm_init(void);

void *pmm_alloc(size_t page_count);
void pmm_free(void *pointer, size_t page_count);

#endif /* _MM_PMM_H */
