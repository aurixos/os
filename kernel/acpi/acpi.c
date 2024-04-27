#include <acpi/acpi.h>
#include <acpi/rsdt.h>
#include <acpi/madt.h>
#include <mm/mm.h>
#include <aurix.h>

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

static bool xsdt_available = false;

static struct rsdt *rsdt;
static struct xsdt *xsdt;

void acpi_init(void *rsdp_addr)
{
	assert(rsdp_addr != NULL);
	
	struct rsdp *rsdp = (struct rsdp *)rsdp_addr;
	rsdt = (struct rsdt *)PHYS_TO_VIRT(rsdp->rsdt_addr);
	// @todo: Check if RSDP is valid
	if (rsdp->revision >= 2) {
		struct xsdp *xsdp = (struct xsdp *)rsdp_addr;
		if (xsdp->xsdt_addr) {
			xsdt = (struct xsdt *)PHYS_TO_VIRT(xsdp->xsdt_addr);
			xsdt_available = true;
		}
	}

	madt_init();

	klog("done");
}

void *acpi_find_sdt(char *signature)
{
	int div = xsdt_available ? 8 : 4;
	int header_length = xsdt_available ? xsdt->header.length : rsdt->header.length;
	int entries = (header_length - sizeof(struct sdt_header)) / div;
	for (int i = 0; i < entries; i++) {
		struct sdt_header *header = NULL;
		if (xsdt_available) {
			header = (struct sdt_header *)(uintptr_t)PHYS_TO_VIRT(xsdt->sdt[i]);
		} else {
			header = (struct sdt_header *)(uintptr_t)PHYS_TO_VIRT(rsdt->sdt[i]);
		}

		if (!strncmp(header->signature, signature, 4)) {
			klog("found header with signature %.4s at %.16llx", header->signature, header);
			return (void *)header;
		}
	}

	return NULL;
}
