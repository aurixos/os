#ifndef _ARCH_CPU_H
#define _ARCH_CPU_H

#include <aurix.h>

#include ARCH_INCLUDE(cpu/cpu.h)

aurix_status cpu_init(void);

void print_backtrace(void);

#endif /* _ARCH_CPU_H */
