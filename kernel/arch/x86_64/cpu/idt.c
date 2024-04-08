#include <arch/x86_64/cpu/idt.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>


interrupt_handler g_int_handlers[16];

extern uint64_t isr_tbl[];

void idt_init()
{
	struct idt_descriptor idt[IDT_MAX_ENTRIES];
	for (size_t i = 0; i < IDT_MAX_ENTRIES; i++) {
		idt_set_entry(&idt[i], isr_tbl[i], IDT_INT_GATE);
	}
	idt_set_entry(&idt[255], isr_tbl[255], IDT_TRAP_GATE);

	for (size_t i = 0; i < 16; i++) {
		g_int_handlers[i] = NULL;
	}

	// @todo: Add 8259 PIC code

	struct idtr idtr;
	idtr.size = sizeof(idt) - 1;
	idtr.base = (uint64_t)&idt;
	idt_load(&idtr);

	klog("done");
}

void idt_set_entry(struct idt_descriptor *entry, uint64_t handler, uint8_t flags)
{
	entry->base_low = handler & 0xffff;
	entry->cs = 0x28;
	entry->ist = 0;
	entry->flags = flags;
	entry->base_mid = (handler >> 16) & 0xffff;
	entry->base_high = handler >> 32;
	entry->reserved = 0;
}