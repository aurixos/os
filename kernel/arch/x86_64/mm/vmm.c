#include <arch/cpu.h>
#include <arch/mm.h>
#include <boot/boot.h>
#include <mm/mm.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

uint64_t *kernel_pt;

void vmm_init(void)
{
	struct limine_memmap_response *memmap = memmap_request.response;

	// set up kernel page table
	kernel_pt = (uint64_t *)pmm_allocz(1);
	if (kernel_pt == NULL) {
		// panic()
		klog("couldn't allocate kernel page table");
		for (;;);
	}

	vmm_map_range(NULL, 0, 0x100000000, 0, VMM_FLAGS_KERNEL_RW, VMM_TYPE_UNCACHEABLE);
	klog("identity mapped 4gb");
	vmm_map_range(NULL, 0, 0x100000000, hhdm_request.response->offset, VMM_FLAGS_KERNEL_RW, VMM_TYPE_UNCACHEABLE);
	klog("mapped 4gb to higher half");

	// map memory
	for (size_t i = 0; i < memmap->entry_count; i++) {
		struct limine_memmap_entry *entry = memmap->entries[i];

		switch (entry->type) {
			case LIMINE_MEMMAP_KERNEL_AND_MODULES:
				uint64_t kernel_virt = kernel_addr_request.response->virtual_base + entry->base - kernel_addr_request.response->physical_base;
				vmm_map_range(NULL, entry->base, entry->base + entry->length, kernel_virt, VMM_FLAGS_KERNEL_RW, VMM_TYPE_UNCACHEABLE);
				klog("entry %d, phys: 0x%lx, virt: 0x%lx, size: %u", i, entry->base, kernel_virt, SIZE_TO_PAGES(entry->length));
				break;
			case LIMINE_MEMMAP_FRAMEBUFFER:
				vmm_map_range(NULL, entry->base, entry->base + entry->length, PHYS_TO_VIRT(entry->base), VMM_FLAGS_KERNEL_RW, VMM_TYPE_WRITE_THROUGH);
				klog("entry %d, phys: 0x%lx, virt: 0x%lx, size: %u", i, entry->base, PHYS_TO_VIRT(entry->base), SIZE_TO_PAGES(entry->length));
				break;
			case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
			case LIMINE_MEMMAP_RESERVED:
				break;
			default:
				if (entry->base + entry->base < 0x100000000) {
					continue;
				}
				vmm_map_range(NULL, entry->base, entry->base + entry->length, PHYS_TO_VIRT(entry->base), VMM_FLAGS_USER_RW, VMM_TYPE_UNCACHEABLE);
				klog("entry %d, phys: 0x%lx, virt: 0x%lx, size: %u", i, entry->base, PHYS_TO_VIRT(entry->base), SIZE_TO_PAGES(entry->length));
				break;
		}
	}

	klog("setting cr3 to 0x%lx (old cr3: 0x%lx)", VIRT_TO_PHYS((uint64_t)kernel_pt), read_cr3());
	write_cr3(VIRT_TO_PHYS((uint64_t)kernel_pt));
	klog("done");
}

void vmm_map(page_table_t *page_table, uintptr_t phys, uintptr_t virt, uint64_t flags, uint64_t type)
{
	// so we don't have to extern the kernel_pt variable
	if (page_table == NULL) {
		page_table = kernel_pt;
	}

	virt = ALIGN_DOWN(virt, PAGE_SIZE);

	// level 4 page mapping index
	size_t pml4_index = (virt & (0x1fful << 39)) >> 39;
	// page directory table index
	size_t pdpt_index = (virt & (0x1fful << 30)) >> 30;
	// page directory index
	size_t pd_index = (virt & (0x1fful << 21)) >> 21;
	// page table index
	size_t pt_index = (virt & (0x1fful << 12)) >> 12;

	uint64_t *pml4 = page_table;
	if (!(pml4[pml4_index] & PTE_PRESENT)) {
		pml4[pml4_index] = (uint64_t)VIRT_TO_PHYS(pmm_allocz(1)) | VMM_FLAGS_KERNEL_RW;
	}

	uint64_t *pdpt = (uint64_t *)PHYS_TO_VIRT((pml4[pml4_index] & ~(0x1ff)));
	if (!(pdpt[pdpt_index] & PTE_PRESENT)) {
		pdpt[pdpt_index] = (uint64_t)VIRT_TO_PHYS(pmm_allocz(1)) | VMM_FLAGS_KERNEL_RW;
	}

	uint64_t *pd = (uint64_t *)PHYS_TO_VIRT((pdpt[pdpt_index] & ~(0x1ff)));
	if (!(pd[pd_index] & PTE_PRESENT)) {
		pd[pd_index] = (uint64_t)VIRT_TO_PHYS(pmm_allocz(1)) | flags | type;
	}

	uint64_t *pt = (uint64_t *)PHYS_TO_VIRT(pd[pd_index] & ~(0x1ff));

	// set mapping
	pt[pt_index] = phys | flags | type;
}

void vmm_unmap(page_table_t *page_table, uintptr_t virt)
{
	// so we don't have to extern the kernel_pt variable
	if (page_table == NULL) {
		page_table = kernel_pt;
	}

	virt = ALIGN_DOWN(virt, PAGE_SIZE);

	// level 4 page mapping index
	size_t pml4_index = (virt & ((uintptr_t)0x1ff << 39)) >> 39;
	// page directory table index
	size_t pdpt_index = (virt & ((uintptr_t)0x1ff << 30)) >> 30;
	// page directory index
	size_t pd_index = (virt & ((uintptr_t)0x1ff << 21)) >> 21;
	// page table index
	size_t pt_index = (virt & ((uintptr_t)0x1ff << 12)) >> 12;

	// get values based on the indexes
	uint64_t *pml4 = page_table;

	if (!(pml4[pml4_index] & PTE_PRESENT)) {
		return;
	}
	uint64_t *pdpt = (uint64_t *)(pml4[pml4_index] & ~(0x1ff));

	if (!(pdpt[pdpt_index] & PTE_PRESENT)) {
		return;
	}
	uint64_t *pd = (uint64_t *)(pdpt[pdpt_index] & ~(0x1ff));

	if (!(pd[pd_index] & PTE_PRESENT)) {
		return;
	}
	uint64_t *pt = (uint64_t *)(pd[pd_index] & ~(0x1ff));

	// set mapping to not present
	pt[pt_index] = 0;

	uint64_t cr3 = PHYS_TO_VIRT(read_cr3());
	if (cr3 == (uint64_t)kernel_pt) {
		invlpg((void *)virt);
	}
}
