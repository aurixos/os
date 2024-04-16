#include <drivers/uart/uart.h>
#include <arch/x86_64/cpu/cpu_utils.h>

void uart_init(int baud)
{
	// @todo: use custom baud rate
	(void)baud;
	outb(COM1 + 1, 0x00);

	// 115200 baud
	outb(COM1 + 3, 0x80);
	outb(COM1, 0x01);
	outb(COM1 + 1, 0x00);

	outb(COM1 + 3, 0x03);
	outb(COM1 + 2, 0xC7);
	outb(COM1 + 4, 0x0B);
	outb(COM1 + 4, 0x0F);
}

void uart_write(char *str)
{
	while (*str) {
		while ((inb(COM1 + 5) & 0x20) == 0)
			;
		outb(COM1, *str++);
	}
}