#include <boot/limine.h>
#include <mm/pmm.h>
#include <utils/round.h>

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

struct buddy_alloc_info pmm_info = {0};

void pmm_init(struct limine_memmap_response *memmap_response)
{
	pmm_info.smallest_bs = BLOCK_SIZE;
	pmm_info.biggest_bs = BLOCK_SIZE * BIG_BLOCK_MULTIPLIER;
	pmm_info.bitmap_size = 16;
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

	// mark every page as used
	memset(pmm_info.bitmap, 0xff, pmm_info.bitmap_size);

	klog("done");
}
