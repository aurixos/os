#ifndef _DEV_TIMER_H
#define _DEV_TIMER_H

#include <time/time.h>
#include <stdint.h>

#define CLOCK_FREQ SEC_TO_USEC(1)

struct timer_regs {
	reg32 control_status;
	reg32 counter_lo;
	reg32 counter_hi;
	reg32 compare[4];
};

#define REGS_TIMER ((struct timer_regs *)(PERIPHERAL_BASE + 0x00003000))

void handle_timer_1();
void handle_timer_3();

#endif /* _DEV_TIMER_H */