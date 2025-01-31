/*********************************************************************************/
/* Module Name:  paging.c                                                        */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024-2025 Jozef Nagy                                            */
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

#include <mm/mman.h>
#include <mm/vmm.h>
#include <lib/string.h>
#include <print.h>
#include <stdint.h>

/* Trimmed down version of */
/* https://github.com/KevinAlavik/nekonix/blob/main/kernel/src/mm/vmm.c */
/* Thanks, Kevin <3 */

void map_page(uintptr_t *pm, uintptr_t virt, uintptr_t phys, uint64_t flags)
{
    uint64_t pml1_idx = (virt & (uint64_t)0x1ff << 12) >> 12;
    uint64_t pml2_idx = (virt & (uint64_t)0x1ff << 21) >> 21;
    uint64_t pml3_idx = (virt & (uint64_t)0x1ff << 30) >> 30;
    uint64_t pml4_idx = (virt & (uint64_t)0x1ff << 39) >> 39;

    if (!(pm[pml4_idx] & 1)) {
        pm[pml4_idx] = (uint64_t)mem_alloc(PAGE_SIZE) | flags;
    }

    uint64_t *pml3_table = (uint64_t *)(pm[pml4_idx] & 0x000FFFFFFFFFF000);
    if (!(pml3_table[pml3_idx] & 1)) {
        pml3_table[pml3_idx] = (uint64_t)mem_alloc(PAGE_SIZE) | flags;
    }

    uint64_t *pml2_table = (uint64_t *)(pml3_table[pml3_idx] & 0x000FFFFFFFFFF000);
    if (!(pml2_table[pml2_idx] & 1)) {
        pml2_table[pml2_idx] = (uint64_t)mem_alloc(PAGE_SIZE) | flags;
    }

    uint64_t *pml1_table = (uint64_t *)(pml2_table[pml2_idx] & 0x000FFFFFFFFFF000);
    pml1_table[pml1_idx] = phys | flags;

	debug("map_page(): Mapped 0x%lx -> 0x%lx\n", phys, virt);
}

uintptr_t *create_pagemap()
{
    uint64_t *pm = (uint64_t *)mem_alloc(PAGE_SIZE);
    if (!pm) {
        debug("create_pagemap(): Failed to allocate memory for a new pm.\n");
        return NULL;
    }
    memset(pm, 0, PAGE_SIZE);

    debug("create_pagemap(): Created new pm at 0x%lx\n", (uint64_t)pm);
    return pm;
}
