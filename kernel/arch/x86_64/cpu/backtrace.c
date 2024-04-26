#include <cpu/cpu.h>
#include <debug/symtable.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

void print_backtrace(void)
{
	uint64_t *base;
	__asm__ volatile("mov %%rbp, %0" : "=g"(base) :: "memory");

	while (1) {
		base = (uint64_t *)*base;
		uint64_t return_addr = *(base + 1);
		
		// 0 is pushed to the stack before calling kernel entry point
		if (return_addr == (uint64_t)NULL || base == NULL || return_addr < (uint64_t)0xffffffff80000000) {
			break;
		}

		// see if the return address is in our symbol table
		int idx = -1;
		for (int i = 0; _symtab[i].addr < UINTPTR_MAX; i++) {
			if (_symtab[i].addr < return_addr && _symtab[i+1].addr >= return_addr) {
				idx = i;
			}
		}
	
		if (idx < 0) {
			_klog("    [%.16lx]  <\?\?\?>\n", return_addr);
		} else {
			_klog("    [%.16lx]  <%s+0x%04x>\n", return_addr, _symtab[idx].name, return_addr - _symtab[idx].addr);
		}
	}

	_klog("End of trace.\n");
}