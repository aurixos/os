#ifndef _UTILS_LOCK_H
#define _UTILS_LOCK_H

#include <arch/cpu.h>

#include <stdint.h>
#include <stdbool.h>

typedef struct spinlock {
	uint8_t lock;
	bool irq;
} spinlock_t;

static inline void spinlock_acquire(spinlock_t *spinlock)
{
	while (__atomic_test_and_set(&spinlock->lock, __ATOMIC_ACQUIRE)) {
#ifdef AURIXOS_x86_64
		__asm__ volatile("pause");
#endif
	}

	spinlock->irq = cpu_get_interrupt_flag();
	cpu_disable_interrupts();
}

static inline void spinlock_release(spinlock_t *spinlock)
{
	if (spinlock->irq) {
		cpu_enable_interrupts();
	} else {
		cpu_disable_interrupts();
	}

	__atomic_clear(spinlock, __ATOMIC_RELEASE);
}

#endif /* _UTILS_LOCK_H */
