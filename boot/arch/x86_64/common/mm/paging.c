/*********************************************************************************/
/* Module Name:  paging.c                                                        */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024 Jozef Nagy                                                 */
/*                                                                               */
/* This source is subject to the MIT License.                                    */
/* See License.txt in the root of this repository.                               */
/* All other rights reserved.                                                    */
/*                                                                               */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE.                                                                     */
/*********************************************************************************/

#include <arch/cpu/cpu.h>
#include <arch/mm/paging.h>
#include <print.h>
#include <axboot.h>

#include <lib/string.h>
#include <stdint.h>
#include <stddef.h>

uint64_t *pagetable = NULL;

int paging_init(void)
{
	// disable write protection
	uint64_t cr0 = read_cr0();
	cr0 &= ~(1 << 16);
	write_cr0(cr0);

	pagetable = (uint64_t *)read_cr3();
	if (pagetable == NULL) {
		log("ERROR: read_cr3() returned NULL!\r\n");
		return 1;
	}

	return 0;
}

void paging_map_range(uint64_t phys, uint64_t virt, size_t npages)
{
	phys = ROUND_UP(phys, PAGE_SIZE);
	virt = ROUND_UP(virt, PAGE_SIZE);

	for (size_t i = 0; i < npages; i++) {
		paging_map(phys + (i * PAGE_SIZE), virt + (i * PAGE_SIZE));
	}
}

void paging_map(uint64_t phys, uint64_t virt)
{
	phys = ROUND_UP(phys, PAGE_SIZE);
	virt = ROUND_UP(virt, PAGE_SIZE);

	uint16_t pt_index = (virt >> 12) & 0x1ff;
	uint16_t pd_index = (virt >> 21) & 0x1ff;
	uint16_t pdpt_index = (virt >> 30) & 0x1ff;
	uint16_t pml4_index = (virt >> 39) & 0x1ff;

	uint64_t *pml4 = (uint64_t *)pagetable;

	uint64_t *pdpt = (uint64_t *)(pml4[pml4_index] & ~(0x1ff));
	if (!(pml4[pml4_index] & PTE_PRESENT)) {
		pdpt = malloc(1 * PAGE_SIZE);
		if (pdpt == NULL) {
			log("ERROR: Failed to allocate memory for page table!\r\n");
			return;
		}

		pml4[pml4_index] = ((uint64_t)pdpt & ~(0x1ff)) | PTE_PRESENT | PTE_READ_WRITE;
	}

	uint64_t *pd = (uint64_t *)(pdpt[pdpt_index] & ~(0x1ff));
	if (!(pdpt[pdpt_index] & PTE_PRESENT)) {
		pd = malloc(1 * PAGE_SIZE);
		if (pd == NULL) {
			log("ERROR: Failed to allocate memory for page table!\r\n");
			return;
		}

		pdpt[pdpt_index] = ((uint64_t)pd & ~(0x1ff)) | PTE_PRESENT | PTE_READ_WRITE;
	}

	uint64_t *pt = (uint64_t *)(pd[pd_index] & ~(0x1ff));
	if (!(pd[pd_index] & PTE_PRESENT)) {
		pt = malloc(1 * PAGE_SIZE);
		if (pt == NULL) {
			log("ERROR: Failed to allocate memory for page table!\r\n");
			return;
		}

		pd[pd_index] = ((uint64_t)pt & ~(0x1ff)) | PTE_PRESENT | PTE_READ_WRITE;
	}

	pt[pt_index] = (phys & ~(0x1ff)) | PTE_PRESENT | PTE_READ_WRITE;

	__asm__ volatile("invlpg (%0)" :: "r"(virt));
}