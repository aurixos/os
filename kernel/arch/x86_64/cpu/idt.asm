%include "arch/x86_64/utils.asm"

global idt_load
idt_load:
	lidt [rdi]
	ret

;;;;

extern cpu_exception_handler

_int_stub:
	cld
	pushaq
	call cpu_exception_handler
	popaq
	add rsp, 16
	iretq

%macro _isr_noerr 1
isr_%+%1:
	push 0
	push %1
	jmp _int_stub
%endmacro

%macro _isr_err 1
isr_%+%1:
	push %1
	jmp _int_stub
%endmacro

_isr_noerr 0
_isr_noerr 1
_isr_noerr 2
_isr_noerr 3
_isr_noerr 4
_isr_noerr 5
_isr_noerr 6
_isr_noerr 7
_isr_err 8
_isr_noerr 9
_isr_err 10
_isr_err 11
_isr_err 12
_isr_err 13
_isr_err 14
_isr_noerr 15
_isr_noerr 16
_isr_err 17
_isr_noerr 18
_isr_noerr 19
_isr_noerr 20
_isr_noerr 21
_isr_noerr 22
_isr_noerr 23
_isr_noerr 24
_isr_noerr 25
_isr_noerr 26
_isr_noerr 27
_isr_noerr 28
_isr_noerr 29
_isr_err 30
_isr_noerr 31

%assign i 32
%rep 224
_isr_noerr i
%assign i i+1
%endrep

section .data

global isr_tbl
isr_tbl:
%assign i 0
%rep 256
	dq isr_%+i
%assign i i+1
%endrep
