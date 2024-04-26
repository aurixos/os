#ifndef _ARCH_CPU_H
#define _ARCH_CPU_H

#include <arch/arch.h>
#include <stdbool.h>

#include ARCH_INCLUDE(cpu/cpu.h)

void cpu_init(void);
void print_backtrace(void);

void cpu_enable_interrupts(void);
void cpu_disable_interrupts(void);
bool cpu_get_interrupt_flag(void);

#endif /* _ARCH_CPU_H */
