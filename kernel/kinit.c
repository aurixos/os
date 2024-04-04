#include <arch/cpu.h>

void _start(void)
{
	cpu_init();
	for (;;);
}
