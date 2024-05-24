OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(AxosInit)

PHDRS
{
	text PT_LOAD FLAGS((1 << 0) | (1 << 2));
	rodata PT_LOAD FLAGS(1 << 2);
	data PT_LOAD FLAGS((1 << 1) | (1 << 2));
}

SECTIONS
{
	. = 0xC0000000;

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