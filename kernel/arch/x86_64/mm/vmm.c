#include <arch/cpu.h>
#include <arch/mm.h>
#include <boot/boot.h>
#include <mm/mm.h>
#include <mm/pmm.h>
#include <mm/vmm.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

uint64_t *kernel_pt = NULL;

extern char _linker_start_text[];
extern char _linker_end_text[];
extern char _linker_start_rodata[];
extern char _linker_end_rodata[];
extern char _linker_start_data[];
extern char _linker_end_data[];

void vmm_init(void)
{
	// set up kernel page table
	kernel_pt = (uint64_t *)pmm_allocz(1);
	if (kernel_pt == NULL) {
		// panic()
		klog("couldn't allocate kernel page table");
		for (;;);
	}

	uintptr_t phys_base = kernel_addr_request.response->physical_base;
	uintptr_t virt_base = kernel_addr_request.response->virtual_base;

	uintptr_t kernel_start_text = ALIGN_DOWN((uintptr_t)_linker_start_text, PAGE_SIZE);
	uintptr_t kernel_end_text = ALIGN_UP((uintptr_t)_linker_end_text, PAGE_SIZE);
	uintptr_t kernel_start_rodata = ALIGN_DOWN((uintptr_t)_linker_start_rodata, PAGE_SIZE);
	uintptr_t kernel_end_rodata = ALIGN_UP((uintptr_t)_linker_end_rodata, PAGE_SIZE);
	uintptr_t kernel_start_data = ALIGN_DOWN((uintptr_t)_linker_start_data, PAGE_SIZE);
	uintptr_t kernel_end_data = ALIGN_UP((uintptr_t)_linker_end_data, PAGE_SIZE);

	// map kernel and 4gb
	for (uintptr_t text = kernel_start_text; text < kernel_end_text; text += PAGE_SIZE) {
		vmm_map(kernel_pt, text - virt_base + phys_base, text, VMM_FLAGS_KERNEL_RO);
	}
	klog("mapped text");
	for (uintptr_t rodata = kernel_start_rodata; rodata < kernel_end_rodata; rodata += PAGE_SIZE) {
		vmm_map(kernel_pt, rodata - virt_base + phys_base, rodata, PTE_PRESENT | PTE_NOEXEC);
	}
	klog("mapped rodata");
	for (uintptr_t data = kernel_start_data; data < kernel_end_data; data += PAGE_SIZE) {
		vmm_map(kernel_pt, data - virt_base + phys_base, data, VMM_FLAGS_KERNEL_RW | PTE_NOEXEC);
	}
	klog("mapped data");

	for (uintptr_t gb = 0; gb < 0x100000000; gb += PAGE_SIZE) {
		vmm_map(kernel_pt, gb, gb, VMM_FLAGS_KERNEL_RW);
		vmm_map(kernel_pt, gb, PHYS_TO_VIRT(gb), VMM_FLAGS_KERNEL_RW);
	}
	klog("mapped 4gb");

	klog("setting cr3 to 0x%lx (old cr3: 0x%lx)", VIRT_TO_PHYS((uint64_t)kernel_pt), read_cr3());
	write_cr3(VIRT_TO_PHYS((uint64_t)kernel_pt));
	klog("done");
}

void vmm_map(page_map_t *page_table, uintptr_t phys, uintptr_t virt, uint64_t flags)
{
	size_t pml4_index = (virt >> 39) & 0x1ff;
	size_t pdpt_index = (virt >> 30) & 0x1ff;
	size_t pd_index = (virt >> 21) & 0x1ff;
	size_t pt_index = (virt >> 12) & 0x1ff;

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
		pd[pd_index] = (uint64_t)VIRT_TO_PHYS(pmm_allocz(1)) | VMM_FLAGS_KERNEL_RW;
	}

	uint64_t *pt = (uint64_t *)PHYS_TO_VIRT((pd[pd_index] & ~(0x1ff)));
	if (!(pt[pt_index] & PTE_PRESENT)) {
		pt[pt_index] = (uint64_t)VIRT_TO_PHYS(pmm_allocz(1)) | VMM_FLAGS_KERNEL_RW;
	}

	// set mapping
	pt[pt_index] = phys | flags;
}

void vmm_unmap(page_map_t *page_table, uintptr_t virt)
{
	size_t pml4_index = (virt >> 39) & 0x1ff;
	size_t pdpt_index = (virt >> 30) & 0x1ff;
	size_t pd_index = (virt >> 21) & 0x1ff;
	size_t pt_index = (virt >> 12) & 0x1ff;

	uint64_t *pml4 = page_table;
	if (!(pml4[pml4_index] & PTE_PRESENT))
		return;

	uint64_t *pdpt = (uint64_t *)PHYS_TO_VIRT((pml4[pml4_index] & ~(0x1ff)));
	if (!(pdpt[pdpt_index] & PTE_PRESENT))
		return;

	uint64_t *pd = (uint64_t *)PHYS_TO_VIRT((pdpt[pdpt_index] & ~(0x1ff)));
	if (!(pd[pd_index] & PTE_PRESENT))
		return;

	uint64_t *pt = (uint64_t *)PHYS_TO_VIRT((pd[pd_index] & ~(0x1ff)));
	if (!(pt[pt_index] & PTE_PRESENT))
		return;

	// set mapping to not present
	pt[pt_index] = 0;

	uint64_t cr3 = PHYS_TO_VIRT(read_cr3());
	if (cr3 == (uint64_t)kernel_pt) {
		invlpg((void *)virt);
	}
}
