#ifndef _CPU_UTILS_H
#define _CPU_UTILS_H

#include <stdint.h>
#include <stdbool.h>

////
// CPU-Related instructions
///

static inline uint32_t read_system_register(void)
{
	uint32_t ret = 0;
	__asm__ volatile("mrs %x0, midr_el1"
					 : "=r"(ret));
	return ret;
}

#endif /* _CPU_UTILS_H */
