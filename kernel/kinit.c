#include <arch/cpu.h>
#include <acpi/acpi.h>
#include <boot/boot.h>
#include <mm/mm.h>
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
	vmm_init();

	acpi_init(rsdp_request.response->address);

	klog("kernel init done");
	for (;;);
}
