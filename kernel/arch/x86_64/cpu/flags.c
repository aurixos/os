#include <stdint.h>
#include <stdbool.h>

bool cpu_get_interrupt_flag(void)
{
	uint64_t rflags;
	__asm__ volatile("pushfq;"
					 "pop %0"
					 : "=r"(rflags));
	return (rflags >> 9) & 1;
}
