#include <arch/aarch64/utils/utils.h>
#include <arch/aarch64/dev/gpio/gpio.h>
#include <arch/aarch64/dev/aux.h>
#include <dev/uart.h>

#include <stdint.h>

#define TXD 14
#define RXD 15

void uart_init()
{
	gpio_pin_set_func(TXD, GFAlt5);
	gpio_pin_set_func(RXD, GFAlt5);
	gpio_pin_enable(TXD);
	gpio_pin_enable(RXD);

	REGS_AUX->enables = 1;
	REGS_AUX->mu_control = 0;
	REGS_AUX->mu_ier = 2;
	REGS_AUX->mu_lcr = 3;
	REGS_AUX->mu_mcr = 0;
	REGS_AUX->mu_baudrate = SYSTEM_CLOCK_FREQ / (8 * (115200 + 1));
	REGS_AUX->mu_control = 3;

	uart_send('\r');
	uart_send('\n');
}

char uart_recv()
{
	while (!(REGS_AUX->mu_lsr & 0x01));
	return REGS_AUX->mu_io & 0xFF;
}

void uart_send(char c)
{
	while (!(REGS_AUX->mu_lsr & 0x20));

	REGS_AUX->mu_io = c;
}

void uart_sendstr(char *s)
{
	while (*s) {
		if (*s == '\n') {
			uart_send('\r');
		}
		uart_send(*s++);
	}
}