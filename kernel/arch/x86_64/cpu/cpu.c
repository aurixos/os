#include <aurix.h>
#include <arch/cpu.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <arch/x86_64/cpu/cpu_utils.h>

aurix_status cpu_init(void)
{
	gdt_init();
	idt_init();

	return AURIX_SUCCESS;
}