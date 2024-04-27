#include <acpi/hpet.h>
#include <time/timer.h>
#include <aurix.h>

#include <stdint.h>
#include <stddef.h>

void (*timer_usleep)(uint64_t);

// the best timer (most precise/reliable)
// will always be registered last
// @todo: find a better way to do this
void timer_register(void *func)
{
	timer_usleep = func;
}

// microseconds
void usleep(uint64_t us)
{
	if (timer_usleep != NULL) {
		timer_usleep(us);
	} else {
		klog("NO TIMER WAS SET UP!");
	}
}

// milliseconds
void sleep(uint64_t ms)
{
	usleep(ms * 1000);
}
