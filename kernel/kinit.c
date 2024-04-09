#include <arch/cpu.h>
#include <aurix.h>

void _start(void)
{
	cpu_init();
	klog("kernel init done");
	for (;;);
}
