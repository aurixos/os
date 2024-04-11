#include <arch/cpu.h>
#include <boot/boot.h>
#include <mm/pmm.h>
#include <aurix.h>

void _start(void)
{
	cpu_init();
	pmm_init(memmap_request.response);
	klog("kernel init done");
	for (;;);
}
