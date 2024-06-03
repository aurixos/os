OUTPUT_FORMAT(binary)
OUTPUT_FORMAT(i386:x86-64)

SECTIONS
{
	. = 0x00007e00;

	_axboot_stage2_start = .;

	.start : {
		*(.start)
	}

	. = ALIGN(0x10);

	_axboot_text_start = .;

	.text : {
		*(.text*)
		*(.gnu.linkonce.t*)
	}

	_axboot_text_end = .;

	. = ALIGN(0x10);

	_axboot_rodata_start = .;

	.rodata : {
		*(.rodata*)
		*(.gnu.linkonce.r*)
	}

	_axboot_rodata_end = .;

	. = ALIGN(0x10);

	_axboot_bss_start = .;

	.bss : {
		*(COMMON)
		*(.bss)
		*(.gnu.linkonce.b*)
	}

	_axboot_bss_end = .;

	. = ALIGN(0x10);

	_axboot_data_start = .;

	.data : {
		*(.data)
		*(.gnu.linkonce.d*)
	}

	_axboot_data_end = .;

	/DISCARD/ : {
		*(.comment)
	}

	_axboot_stage2_end = ALIGN(CONSTANT(MAXPAGESIZE));
}
