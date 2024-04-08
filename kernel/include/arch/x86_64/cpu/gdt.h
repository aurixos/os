#ifndef _CPU_GDT_H
#define _CPU_GDT_H

#include <stdint.h>

struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_high : 4;
	uint8_t flags : 4;
	uint8_t base_high;
} __attribute__((packed));

struct gdtr {
	uint16_t size;
	uint64_t offset;
} __attribute__((packed));

extern void gdt_load(struct gdtr *gdtr);

void gdt_init(void);

void gdt_set_entry(struct gdt_entry *entry, uint32_t base, uint32_t limit, uint8_t access,
				   uint8_t flags);

#endif /* _CPU_GDT_H */
