#include <drivers/uart/uart.h>
#include <mm/mmio.h>

static uint8_t uart_is_ready_to_write(void)
{
	return mmio_read(AUX_MU_LSR_REG) & 0x20;
}

static void uart_write_byte_blocking(unsigned char c)
{
	while (!uart_is_ready_to_write());
	mmio_write(AUX_MU_IO_REG, (uint8_t)c);
}

void uart_init(int baud)
{
	// enable UART1
	mmio_write(AUX_ENABLES, 1);
	mmio_write(AUX_MU_IER_REG, 0);
	mmio_write(AUX_MU_CNTL_REG, 0);
	mmio_write(AUX_MU_LCR_REG, 3);	
	mmio_write(AUX_MU_MCR_REG, 0);	
	mmio_write(AUX_MU_IER_REG, 0);
	// disable interrupts
	mmio_write(AUX_MU_IIR_REG, 0xC6);
	mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(baud));

	gpio_use_as_alt5(14);
	gpio_use_as_alt5(15);

	// enable RX/TX
	mmio_write(AUX_MU_CNTL_REG, 3);
}

void uart_write(char *str)
{
	while (*str) {
		if (*str == '\n') {
			uart_write_byte_blocking('\r');
		}
		uart_write_byte_blocking(*str++);
	}
}