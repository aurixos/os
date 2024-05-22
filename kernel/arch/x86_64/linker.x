OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)

PHDRS
{
	text PT_LOAD FLAGS((1 << 0) | (1 << 2));
	rodata PT_LOAD FLAGS(1 << 2);
	data PT_LOAD FLAGS((1 << 1) | (1 << 2));
	dynamic PT_DYNAMIC FLAGS((1 << 1) | (1 << 2));
}

SECTIONS
{
	/* Limine will relocate this to 0xffffffff80000000. */
	/* Future me, please keep this in mind when
	/* working on AxBoot. */
	. = 0;

	.text : {
		*(.text .text.*)
	} :text

	. = ALIGN(CONSTANT(MAXPAGESIZE));

	.rodata : {
		*(.rodata .rodata.*)
	} :rodata

	. = ALIGN(CONSTANT(MAXPAGESIZE));

	.data : {
		*(.data .data.*)
	} :data

	.dynamic : {
		*(.dynamic)
	} :data :dynamic

	.bss : {
		*(COMMON)
		*(.bss .bss.*)
	} :data

	/DISCARD/ : {
		*(.eh_frame)
		*(.note .note.*)
	}
}