.section ".text.boot"

.global _start
_start:
	// make sure we're executing on the main core
	mrs x1, mpidr_el1
	and x1, x1, #3
	cbz x1, 2f

// we're not on the main core
1:
	wfe
	b 1b
// else
2:
	ldr x1, =_start
	mov sp, x1

	// BSS cleanup
	ldr x1, =__bss_start
	ldr w2, =__bss_size
3:
	cbz w2, 4f
	str xzr, [x1], #8
	sub w2, w2, #1
	cbnz w2, 3b

4:
	// jump to the kernel
	bl main
	// halt main core if we ever return
	b 1b
