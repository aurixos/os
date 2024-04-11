#ifndef _MM_PMM_H
#define _MM_PMM_H

#include <arch/mm.h>
#include <boot/boot.h>

#include <stdint.h>

#define BIG_BLOCK_MULTIPLIER (1ull << (MAX_LAYER_COUNT - 1))

#define PHYS_TO_VIRT(addr) ((addr) + hhdm_request.response->offset)

struct buddy_alloc_info {
	// smallest block size
	uint64_t smallest_bs;

	// biggest block size
	uint64_t biggest_bs;

	// bitmap & bitmap size
	uint8_t *bitmap;
	uint64_t bitmap_size;
	
	// block count on layer 0
	uint64_t bcl0;
};

void pmm_init(struct limine_memmap_response *memmap_response);

#endif /* _MM_PMM_H */
