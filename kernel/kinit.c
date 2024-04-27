#include <arch/cpu.h>
#include <acpi/acpi.h>
#include <boot/boot.h>
#include <mm/mm.h>
#include <time/timer.h>
#include <aurix.h>

#include <string.h>

void _start(void)
{
	cpu_init();

	acpi_init(rsdp_request.response->address);

	klog("kernel init done");
	for (;;);
}
