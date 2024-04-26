#include <arch/cpu.h>
#include <acpi/acpi.h>
#include <boot/boot.h>
#include <mm/pmm.h>

#include <aurix.h>

void _start(void)
{
	cpu_init();
	pmm_init();

	acpi_init(rsdp_request.response->address);

	klog("kernel init done");
	for (;;);
}
