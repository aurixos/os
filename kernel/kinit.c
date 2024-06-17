#include <dev/uart.h>
#include <aurix.h>

void kinit(void)
{
	uart_init();
	uart_sendstr("\n\n");
	uart_sendstr("Welcome to AurixOS!\n");

	for (;;) {
		uart_send(uart_recv());
	}
}
