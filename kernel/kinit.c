#include <arch/cpu.h>
#include <aurix.h>

void _start(void)
{
	cpu_init();
	__asm__("int $0x03");
	klog("kernel init done");
	for (;;);
}
