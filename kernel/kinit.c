#include <aurix.h>
#include <dev/uart.h>
#include <time/timer.h>
#include ARCH_INCLUDE(cpu/irq.h)

void kinit(void)
{
	uart_init();
	uart_sendstr("\n\n");
	uart_sendstr("Welcome to AurixOS!\n");

	irq_init_vectors();
	enable_interrupt_controller();
	irq_enable();

	timer_init();

	for (;;);
}
