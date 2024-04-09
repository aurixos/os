#include <arch/x86_64/cpu/idt.h>
#include <arch/x86_64/drivers/pic/pic.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

interrupt_handler irq_handlers[16];
extern uint64_t isr_tbl[];

void idt_init()
{
	struct idt_descriptor idt[IDT_MAX_ENTRIES];

	// exceptions
	for (size_t i = 0; i < 32; i++) {
		idt_set_entry(&idt[i], isr_tbl[i], IDT_TRAP_GATE);
	}

	// interrupts
	for (size_t i = 32; i < IDT_MAX_ENTRIES; i++) {
		idt_set_entry(&idt[i], isr_tbl[i], IDT_INT_GATE);
	}

	for (size_t i = 0; i < 16; i++) {
		irq_handlers[i] = NULL;
	}

	// @todo: Add 8259 PIC code
	pic_init();
	pic_disable();

	struct idtr idtr;
	idtr.size = (uint16_t)sizeof(idt) - 1;
	idtr.base = (uint64_t)&idt;
	idt_load(&idtr);

	klog("done");
}

void idt_set_entry(struct idt_descriptor *entry, uint64_t handler, uint8_t flags)
{
	entry->base_low = handler & 0xffff;
	entry->cs = 0x08;
	entry->ist = 0;
	entry->flags = flags;
	entry->base_mid = (handler >> 16) & 0xffff;
	entry->base_high = handler >> 32;
	entry->reserved = 0;
}
