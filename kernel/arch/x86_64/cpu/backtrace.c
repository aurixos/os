#include <cpu/cpu.h>
#include <debug/symtable.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

void print_backtrace(void)
{
	uint64_t *base;
	__asm__ volatile("mov %%rbp, %0" : "=g"(base) :: "memory");
	struct stackframe *frame = (struct stackframe *)*base;

	while (1) {
		// 0 is pushed to the stack before calling kernel entry point
		if (frame->rip == (uint64_t)NULL || base == NULL || frame->rip < (uint64_t)0xffffffff80000000) {
			break;
		}

		// see if the return address is in our symbol table
		int idx = -1;
		for (int i = 0; _symtab[i].addr < UINTPTR_MAX; i++) {
			if (_symtab[i].addr < frame->rip && _symtab[i+1].addr >= frame->rip) {
				idx = i;
			}
		}
	
		if (idx < 0) {
			_klog("    [%.16lx]  <\?\?\?>\n", frame->rip);
		} else {
			_klog("    [%.16lx]  <%s+0x%04x>\n", frame->rip, _symtab[idx].name, frame->rip - _symtab[idx].addr);
		}

		// proceed to the next trace
		frame = frame->rbp;
	}

	_klog("End of trace.\n");
}
