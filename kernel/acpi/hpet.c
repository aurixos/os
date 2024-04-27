#include <acpi/acpi.h>
#include <acpi/hpet.h>
#include <mm/mm.h>
#include <time/timer.h>

#include <stdint.h>
#include <stddef.h>

struct hpet_regs *hpet_regs;

void hpet_init(void)
{
	struct acpi_hpet *hpet = (struct acpi_hpet *)acpi_find_sdt("HPET");
	if (hpet == NULL) {
		klog("couldn't find HPET table");
		return;
	}

	hpet_regs = (struct hpet_regs *)PHYS_TO_VIRT(hpet->addr);
	hpet_regs->counter_val = 0;
	hpet_regs->general_config = 1;

	timer_register(&hpet_usleep);
}

void hpet_usleep(uint64_t us)
{
	uint32_t clock_period = hpet_regs->capabilities >> 32;
	volatile size_t target_val = hpet_regs->counter_val + (us * (1000000000 / clock_period));
	while (hpet_regs->counter_val < target_val) {
#ifdef AURIXOS_x86_64
		__asm__ volatile("pause");
#endif
	}
}
