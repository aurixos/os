#ifndef _ARCH_CPU_IDT_H
#define _ARCH_CPU_IDT_H

#include <stdint.h>

#define IDT_MAX_ENTRIES 256

#define IDT_INT_GATE 0x8e
#define IDT_TRAP_GATE 0x8f

struct idt_descriptor {
	uint16_t base_low;
	uint16_t cs;
	uint8_t ist;
	uint8_t flags;
	uint16_t base_mid;
	uint32_t base_high;
	uint32_t reserved;
} __attribute__((packed));

struct idtr {
	uint16_t size;
	uint64_t base;
} __attribute__((packed));

typedef void (*interrupt_handler)();

void idt_init();
void idt_set_entry(struct idt_descriptor *entry, uint64_t handler, uint8_t flags);

extern void idt_load(struct idtr *idtr);

#endif /* _ARCH_CPU_IDT_H */
