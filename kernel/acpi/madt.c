#include <acpi/acpi.h>
#include <acpi/madt.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

static struct madt *madt;

void madt_init(void)
{
	madt = acpi_find_sdt("APIC");
	if (madt == NULL) {
		klog("couldn't find MADT table");
		return;
	}
}