#include <arch/cpu.h>
#include <mm/pmm.h>

#include <aurix.h>

void _start(void)
{
	cpu_init();
	pmm_init();

	klog("kernel init done");
	for (;;);
}
