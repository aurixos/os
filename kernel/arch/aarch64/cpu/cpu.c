#include <arch/cpu.h>
#include <arch/mmio.h>
#include <drivers/uart/uart.h>
#include <cpu/cpu_utils.h>
#include <aurix.h>

uint64_t MMIO_BASE = 0;

void cpu_early_init(void)
{
	// detect board we're running on
	uint32_t board = (read_system_register() >> 4) & 0xFFF;
	switch (board) {
		case 0xd03: // rpi3
			MMIO_BASE = 0x3f000000;
			break;
		case 0xd08: // rpi4
			MMIO_BASE = 0xfe000000;
			break;
		default: // qemu virt
			MMIO_BASE = 0x20000000;
			break;
	}

	// initialize uart0 and uart1
	uart_init(115200);
}