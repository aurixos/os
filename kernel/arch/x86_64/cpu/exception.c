#include <arch/x86_64/cpu/exception.h>
#include <aurix.h>

void cpu_exception_handler(struct interrupt_frame frame)
{
	(void)frame;
	// @todo: implement an exception handler
	klog("EXCEPTION!");
	for (;;) {
		__asm__ volatile("cli;hlt");
	}
}