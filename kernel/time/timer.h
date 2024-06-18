#ifndef _TIME_TIMER_H
#define _TIME_TIMER_H

#include <stdint.h>

void timer_init();
u64 timer_get_ticks();
void timer_sleep(u32 ms);

#endif /* _TIME_TIMER_H */