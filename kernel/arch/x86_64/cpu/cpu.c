#include <arch/cpu.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <cpu/cpu_utils.h>
#include <drivers/uart/uart.h>

#include <aurix.h>

uint64_t MMIO_BASE = 0;

void cpu_init(void)
{
	uart_init(115200);

	gdt_init();
	idt_init();

	klog("early init");
}

void cpu_enable_interrupts(void)
{
	__asm__ volatile("sti");
}

void cpu_disable_interrupts(void)
{
	__asm__ volatile("cli");
}
