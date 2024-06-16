#ifndef _ARCH_UTILS_UTILS_H
#define _ARCH_UTILS_UTILS_H

#include <stdint.h>

void tdelay(u64 ticks);

void outl(u64 addr, u32 val);
u32 inl(u64 addr);

#endif /* _ARCH_UTILS_UTILS_H */