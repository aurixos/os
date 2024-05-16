#include <arch/cpu.h>
#include <arch/mmio.h>
#include <drivers/uart/uart.h>
#include <aurix.h>

uint64_t MMIO_BASE = 0;

void cpu_early_init(void)
{
	// @todo: detect board to set correct MMIO port
	// defaults to rpi3b
	MMIO_BASE = 0x3f000000;

	uart_init(115200);
}