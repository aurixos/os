#include <dev/uart.h>
#include <aurix.h>

void kinit(void)
{
	uart_init();
	uart_sendstr("Welcome to AurixOS!\n");

	for (;;);
}
