#ifndef _ACPI_ACPI_H
#define _ACPI_ACPI_H

#include <stdint.h>
#include <stdbool.h>

struct sdt_header {
	char signature[4];
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oem_id[6];
	char oem_tableid[8];
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;
} __attribute__((packed));

struct rsdp {
	char signature[8];
	uint8_t checksum;
	char oem_id[6];
	uint8_t revision;
	uint32_t rsdt_addr;
} __attribute__((packed));

struct xsdp {
	struct rsdp rsdp;
	uint32_t length;
	uint64_t xsdt_addr;
	uint8_t checksum;
	uint8_t reserved[3];
} __attribute__((packed));

void acpi_init(void *rsdp_addr);

void *acpi_find_sdt(char *signature);
bool acpi_verify_checksum(struct sdt_header *header);

#endif /* _ACPI_ACPI_H */
