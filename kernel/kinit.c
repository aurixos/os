#include <arch/cpu.h>
#include <acpi/acpi.h>
#include <boot/boot.h>
#include <mm/mm.h>
#include <mm/pmm.h>
#include <time/timer.h>
#include <aurix.h>

#include <string.h>

void _start(void)
{
	// this should initialize basic CPU features
	// and enumerate the CPU's available functions
	// (optionally the board we're running on)
	cpu_early_init();
	cpu_enable_interrupts();

	pmm_init();

	// for some reason memset() triggers a page fault
	// on allocated memory
#if 0
	// pmm test
	void *ptr = pmm_allocz(1);
	memset(ptr, 0x41, 2);
	klog("%s", ptr);
	pmm_free(ptr, 1);
#endif

	acpi_init(rsdp_request.response->address);

	klog("kernel init done");
	for (;;);
}
