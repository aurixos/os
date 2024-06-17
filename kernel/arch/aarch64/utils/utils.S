.globl tdelay
tdelay:
	subs x0, x0, #1
	bne tdelay
	ret

.globl outl
outl:
	str w1, [x0]
	ret

.globl inl
inl:
	ldr w0, [x0]
	ret

.globl get_el
get_el:
	mrs x0, CurrentEL
	lsr x0, x0, #2
	ret
