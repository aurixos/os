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

#ifdef AURIXOS_x86_64
struct madt_lapic {
    struct madt_header header;
    uint8_t acpi_processor_id;
    uint8_t apic_id;
    uint32_t flags;
} __attribute__((packed));

struct madt_ioapic {
    struct madt_header header;
    uint8_t ioapic_id;
    uint8_t reserved;
    uint32_t ioapic_address;
    uint32_t gsi_base;
} __attribute__((packed));

struct madt_iso {
    struct madt_header header;
    uint8_t bus_source;
    uint8_t irq_source;
    uint32_t gsi;
    uint16_t flags;
} __attribute__((packed));

struct madt_lapic_nmi {
    struct madt_header header;
    uint8_t acpi_processor_id;
    uint16_t flags;
    uint8_t lint;
} __attribute__((packed));
#endif

void madt_init(void);

#endif /* _ACPI_MADT_H */
