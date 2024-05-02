#ifndef _ACPI_MADT_H
#define _ACPI_MADT_H

#include <acpi/acpi.h>

#include <stdint.h>

struct madt_header {
	uint8_t type;
	uint8_t length;
} __attribute__((packed));

struct acpi_madt {
	struct sdt_header header;
	uint32_t lic_addr;
	uint32_t flags;
	struct madt_header entry[];
} __attribute__((packed));

void madt_init(void);

#endif /* _ACPI_MADT_H */
