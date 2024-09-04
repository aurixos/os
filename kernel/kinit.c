#include "../boot/include/protocol/abp.h"

void _start(struct abp_boot_info *bootinfo)
{
	for (;;) {
		__asm__ volatile("cli;hlt");
	}
}