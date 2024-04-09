global gdt_load
gdt_load:
	lgdt [rdi]
	push 0x08
	lea rax, [rel .reload_cs]
	push rax
	retfq

.reload_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
