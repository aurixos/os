#include <boot/limine.h>
#include <mm/pmm.h>
#include <utils/round.h>

#include <stdint.h>
#include <stddef.h>

struct buddy_alloc_info pmm_info = {0};

static inline uint64_t block_count_on_layer(int layer)
{
	return (1ull << layer) * pmm_info.bcl0;
}

static inline uint64_t index_of_layer(int layer)
{
	return ROUND_UP(pmm_info.bcl0, (sizeof(pmm_info.bitmap[0] * 8))) * ((1ull << layer) - 1);
}

void pmm_init(struct limine_memmap_response *memmap_response)
{
	pmm_info.smallest_bs = BLOCK_SIZE;
	pmm_info.biggest_bs = BLOCK_SIZE * BIG_BLOCK_MULTIPLIER;
	pmm_info.bitmap_size = index_of_layer(MAX_LAYER_COUNT);
	pmm_info.bitmap = NULL;

	// find large enough memory to fit the bitmap into
	for (uint64_t i = 0; i < memmap_response->entry_count; i++) {
		struct limine_memmap_entry *entry = memmap_response->entries[i];
		if (entry->type != LIMINE_MEMMAP_USABLE &&
			entry->type != LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
			continue;
		}

		// found one!
		if (entry->length >= pmm_info.bitmap_size) {
			pmm_info.bitmap = (uint8_t *)PHYS_TO_VIRT(entry->base);
			break;
		}
	}

	if (pmm_info.bitmap == NULL) {
		klog("Couldn't allocate memory for bitmap!");
		for (;;);
	}

	klog("done");
}
