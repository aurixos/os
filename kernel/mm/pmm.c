#include <boot/boot.h>
#include <data/bmap.h>
#include <mm/mm.h>
#include <aurix.h>

#include <stdint.h>
#include <string.h>

struct pmm_info pmm_info;

static void *find_free_range(size_t npages)
{
	for (size_t addr = 0; addr < PAGE_TO_BIT(pmm_info.mem_top); addr++) {
		for (size_t page = 0; page < npages; page++) {
			if (bitmap_get(&pmm_info.bitmap, addr + PAGE_TO_BIT(page)))
				break;

			if (page == npages - 1)
				return (void *)BIT_TO_PAGE(addr);
		}
	}

	return NULL;
}

static char *get_entry_type(uint64_t type)
{
	switch (type) {
	case LIMINE_MEMMAP_USABLE:
		return "Usable";
	case LIMINE_MEMMAP_RESERVED:
		return "Reserved";
	case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
		return "ACPI Reclaimable";
	case LIMINE_MEMMAP_ACPI_NVS:
		return "ACPI NVS";
	case LIMINE_MEMMAP_BAD_MEMORY:
		return "Bad Memory";
	case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
		return "Bootloader Reclaimable";
	case LIMINE_MEMMAP_KERNEL_AND_MODULES:
		return "Kernel and Modules";
	case LIMINE_MEMMAP_FRAMEBUFFER:
		return "Framebuffer";
	default:
		return "???";
	}
}

void pmm_init()
{
	struct limine_memmap_response *memmap = memmap_request.response;
	size_t current_page_top = 0;

	// process memory map
	for (uint64_t i = 0; i < memmap->entry_count; i++) {
		struct limine_memmap_entry *entry = memmap->entries[i];

#ifdef _DEBUG
		klog("entry %i base 0x%lx, length %lu, type %s", i, entry->base,
			 entry->length, get_entry_type(entry->type));
#endif

		if (entry->type != LIMINE_MEMMAP_USABLE &&
				entry->type != LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE &&
				entry->type != LIMINE_MEMMAP_KERNEL_AND_MODULES) {
			continue;
		}

		current_page_top = entry->base + entry->length;

		if (current_page_top > pmm_info.mem_top) {
			pmm_info.mem_top = current_page_top;
		}
	}

	pmm_info.used_pages = KB_TO_PAGES(pmm_info.mem_top);
	pmm_info.bitmap.size = ALIGN_UP(ALIGN_DOWN(pmm_info.mem_top, PAGE_SIZE) / PAGE_SIZE / 32, PAGE_SIZE);

	for (uint64_t i = 0; i < memmap->entry_count; i++) {
		struct limine_memmap_entry *entry = memmap->entries[i];

		if (entry->type != LIMINE_MEMMAP_USABLE) {
			continue;
		}

		if (entry->length >= pmm_info.bitmap.size) {
			pmm_info.bitmap.map = (uint32_t *)PHYS_TO_VIRT(entry->base);

			entry->base += pmm_info.bitmap.size;
			entry->length -= pmm_info.bitmap.size;

			break;
		}
	}

	// mark everything as used
	memset((void *)pmm_info.bitmap.map, 0xFF, pmm_info.bitmap.size);

	// ...and mark all usable entries as free
	for (uint64_t i = 0; i < memmap->entry_count; i++) {
		struct limine_memmap_entry *entry = memmap->entries[i];

		if (entry->type == LIMINE_MEMMAP_USABLE) {
			pmm_free((void *)entry->base, entry->length / PAGE_SIZE);
		}
	}

	// reserve nullptr
	bitmap_set(&pmm_info.bitmap, 0);

	klog("init done");
}

void *pmm_alloc(size_t npages)
{
	if (pmm_info.used_pages <= 0) {
		return NULL;
	}

	// maybe panic() to signalize we're out of memory?
	void *ptr = find_free_range(npages);
	if (ptr == NULL)
		return NULL;

	uint64_t index = PAGE_TO_BIT(ptr);
	for (size_t i = 0; i < npages; i++) {
		bitmap_set(&pmm_info.bitmap, index + i);
	}

	pmm_info.used_pages += npages;

	return (void *)PHYS_TO_VIRT(BIT_TO_PAGE(index));
}

void *pmm_allocz(size_t npages)
{
	void *ptr = pmm_alloc(npages);
	if (ptr == NULL) {
		return NULL;
	}

	memset(ptr, 0, npages * PAGE_SIZE);
	return ptr;
}

void pmm_free(void *ptr, size_t npages)
{
	uint64_t index = PAGE_TO_BIT(VIRT_TO_PHYS(ptr));

	for (size_t i = 0; i < npages; i++) {
		bitmap_clear(&pmm_info.bitmap, index + i);
	}

	pmm_info.used_pages -= npages;
}

size_t pmm_get_highest_page(void)
{
	return pmm_info.mem_top;
}
