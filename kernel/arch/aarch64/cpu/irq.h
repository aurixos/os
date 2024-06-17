#ifndef _CPU_IRQ_H
#define _CPU_IRQ_H

void irq_init_vectors();
void enable_interrupt_controller();
void irq_enable();
void irq_disable();

#ifndef __ASSEMBLER__

#include <machine.h>
#include <stdint.h>

// video core
enum vc_irqs {
	AUX_IRQ = (1 << 29)
};

struct arm_irq_regs_2711 {
	reg32 irq0_pending_0;
	reg32 irq0_pending_1;
	reg32 irq0_pending_2;
	reg32 res0;
	reg32 irq0_enable_0;
	reg32 irq0_enable_1;
	reg32 irq0_enable_2;
	reg32 res1;
	reg32 irq0_disable_0;
	reg32 irq0_disable_1;
	reg32 irq0_disable_2;
};

struct arm_irq_regs_2837 {
	reg32 irq0_pending_0;
	reg32 irq0_pending_1;
	reg32 irq0_pending_2;
	reg32 fiq_control;
	reg32 irq0_enable_0;
	reg32 irq0_enable_1;
	reg32 irq0_enable_2;
	reg32 res;
	reg32 irq0_disable_0;
	reg32 irq0_disable_1;
	reg32 irq0_disable_2;
};

#if MACHINE_VERSION == 3
typedef struct arm_irq_regs_2837 arm_irq_regs;
#elif MACHINE_VERSION == 4
typedef struct arm_irq_regs_2711 arm_irq_regs;
#endif

#define REGS_IRQ ((arm_irq_regs *)(PERIPHERAL_BASE + 0x0000B200))

#endif

#endif /* _CPU_IRQ_H */
