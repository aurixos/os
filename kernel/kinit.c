#include <boot/abp.h>
#include <debug/uart.h>

void _start(struct abp_boot_info *bootinfo)
{
	serial_init();
	serial_sendstr("Hello from AurixOS!\n");

	for (;;) {
		__asm__ volatile("cli;hlt");
	}
}