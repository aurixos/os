#include <arch/aarch64/mm/mm.h>

.section ".text.boot"

.globl _start
_start:
	mrs x0, mpidr_el1
	and x0, x0, #0xFF
	cbz x0, setup
	b hang

setup:
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