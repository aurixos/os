/*********************************************************************************/
/* Module Name:  handoff.c                                                       */
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
#include <arch/cpu/gdt.h>
#include <arch/mm/paging.h>
#include <protocol/abp.h>
#include <print.h>
#include <axboot.h>

#include <stdint.h>

struct gdt {
	struct gdt_descriptor null;
	struct gdt_descriptor kernelcode32;
	struct gdt_descriptor kerneldata32;
	struct gdt_descriptor kernelcode64;
	struct gdt_descriptor kerneldata64;
	struct tss_descriptor tss;
};

void abp_handoff(void *entrypoint, struct abp_boot_info *bootinfo, void *stack, uint16_t stack_size)
{
	// load new GDT
	struct gdt gdt = {0};
	struct gdtr gdtr = {0};
	struct tss tss = {0};

	tss.iomap_base = sizeof(struct tss);
	uint64_t tss_addr = (uint64_t)&tss;

	gdt_set_entry(&gdt.null, 0, 0, 0, 0);
	gdt_set_entry(&gdt.kernelcode32, 0, 0xFFFF, 0x9a, 0x0a);
	gdt_set_entry(&gdt.kerneldata32, 0, 0xFFFF, 0x92, 0x0c);
	gdt_set_entry(&gdt.kernelcode64, 0, 0, 0x9a, 0x0a);
	gdt_set_entry(&gdt.kerneldata64, 0, 0, 0x92, 0x0c);

	gdt_set_entry(&gdt.tss.gdt, tss_addr, sizeof(tss) - 1, 0x89, 0x00);
	gdt.tss.base_high = (tss_addr >> 32) & 0xFFFFFFFF;
	gdt.tss.reserved = 0;

	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint64_t)&gdt;

	void *pml4 = (void *)paging_get_pml4();

	// ...disable interrupts
	cpu_disable_interrupts();

	// it's go time, motherfuckers!
	__asm__ volatile(
		"movq %[pml4], %%cr3\n"

		"lgdt %[gdt]\n"
		"ltr %[tss]\n"

		"pushq $0x18\n"
		"leaq 1f(%%rip), %%rax\n"
		"pushq %%rax\n"
		"lretq\n"

		"1:\n"
		"movq $0x20, %%rax\n"
		"movq %%rax, %%ds\n"
		"movq %%rax, %%es\n"
		"movq %%rax, %%fs\n"
		"movq %%rax, %%gs\n"
		"movq %%rax, %%ss\n"

		"movq %[stack], %%rsp\n"

		"pushq $0x00\n"
		"callq *%[entryp]\n"
		::
			[pml4]"r"(pml4),
			[gdt]"m"(gdtr),
			[tss]"r"((uint16_t)0x28),
			[stack]"gm"((uint64_t)stack + (stack_size * PAGE_SIZE)),
			[entryp]"r"(entrypoint), "c"(bootinfo)
		: "rax", "memory");

	__builtin_unreachable();
}