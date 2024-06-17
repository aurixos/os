#include <arch/aarch64/mm/mm.h>
#include <arch/aarch64/cpu/sysregs.h>

.section ".text.boot"

.globl _start
_start:
	mrs x0, mpidr_el1
	and x0, x0, #0xFF
	cbz x0, setup
	b hang

setup:
	ldr x0, =SCTLR_VALUE_MMU_DISABLED
	msr sctlr_el1, x0

	ldr x0, =HCR_VALUE
	msr hcr_el2, x0

	ldr x0, =SCR_VALUE
	msr scr_el3, x0

	ldr x0, =SPSR_VALUE
	msr spsr_el3, x0

	adr x0, el1_entry
	msr elr_el3, x0

el1_entry:
	adr x0, __bss_start
	adr x1, __bss_end
	sub x1, x1, x0
	bl memzero

	mov sp, #LOW_MEMORY
	bl kinit
	b hang

hang:
	wfe
	b hang