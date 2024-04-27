#ifndef _TIME_TIMER_H
#define _TIME_TIMER_H

void timer_register(void *func);

void usleep(uint64_t us);
void sleep(uint64_t ms);

#endif /* _TIME_TIMER_H */
