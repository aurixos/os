#ifndef _ACPI_RSDT_H
#define _ACPI_RSDT_H

#include <acpi/acpi.h>

struct rsdt {
	struct sdt_header header;
	uint32_t sdt[];
} __attribute__((packed));

struct xsdt {
	struct sdt_header header;
	uint64_t sdt[];
} __attribute__((packed));

#endif /* _ACPI_RSDT_H */
