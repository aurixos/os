/* We can't use this linker yet, as AxBoot doesn't support */
/* Higher half kernel loading yet. */

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
	. = 0xffffffff80000000;

	_linker_start_text = .;

	.text : {
		*(.text .text.*)
	} :text

	_linker_end_text = .;

	. = ALIGN(CONSTANT(MAXPAGESIZE));

	_linker_start_rodata = .;

	.rodata : {
		*(.rodata .rodata.*)
	} :rodata
	
	_linker_end_rodata = .;

	. = ALIGN(CONSTANT(MAXPAGESIZE));

	_linker_start_data = .;

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

	_linker_end_data = .;

	/DISCARD/ : {
		*(.eh_frame)
		*(.note .note.*)
	}
}