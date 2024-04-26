#ifndef _CPU_CPU_H
#define _CPU_CPU_H

#include "cpu_utils.h"

struct stackframe {
	struct stackframe *rbp;
	uint64_t rip;
} __attribute__((packed));

#endif /* _CPU_CPU_H */
