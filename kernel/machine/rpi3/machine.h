#ifndef _MACHINE_MACHINE_H
#define _MACHINE_MACHINE_H

#include "periph.h"

// Raspberry Pi 3
#define MACHINE_VERSION 3

#define SYSTEM_CLOCK_FREQ (250000000)
#define CORE_CLOCK_FREQ (1500000000)

void machine_init();

#endif /* _MACHINE_MACHINE_H */