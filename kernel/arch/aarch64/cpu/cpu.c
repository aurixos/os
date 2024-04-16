#include <arch/cpu.h>
#include <arch/mmio.h>
#include <drivers/uart/uart.h>
#include <aurix.h>

uint64_t MMIO_BASE = 0;

aurix_status cpu_init(void)
{
	// @todo: detect board to set correct MMIO port
	// defaults to rpi3b
	MMIO_BASE = 0x3F000000;

	uart_init(115200);

	return AURIX_SUCCESS;
}