#include <acpi/acpi.h>
#include <acpi/madt.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

static struct acpi_madt *madt;

void madt_init(void)
{
	madt = (struct acpi_madt *)acpi_find_sdt("APIC");
	if (madt == NULL) {
		klog("couldn't find MADT table");
		return;
	}

	uint8_t *ptr = (uint8_t *)&madt->entry;
	uint8_t *end = (uint8_t *)&madt->header + madt->header.length;

	while (ptr < end) {
		struct madt_header *header = (struct madt_header *)ptr;
		switch (header->type) {
		case 0:
			klog("found lapic");
			break;
		case 1:
			klog("found ioapic");
			break;
		case 2:
			klog("found ioapic iso");
			break;
		case 3:
			klog("found ioapic nmi source");
			break;
		case 4:
			klog("found lapic nmi");
			break;
		case 5:
			klog("found lapic addr override");
			break;
		case 9:
			klog("found x2lapic entry");
			break;
		default:
			break;
		}
		ptr += header->length;
	}
}