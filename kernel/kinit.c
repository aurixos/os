#include "../boot/include/protocol/abp.h"

void _start(struct abp_boot_info *bootinfo)
{
	__asm__ volatile("int $0x01");
	for (;;) {
		__asm__ volatile("cli;hlt");
	}
}