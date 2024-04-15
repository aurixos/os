#include <arch/cpu.h>
#include <boot/boot.h>
#include <aurix.h>

void _start(void)
{
	cpu_init();

	klog("kernel init done");
	for (;;);
}
