#ifndef _ARCH_MM_MM_H
#define _ARCH_MM_MM_H

#define PAGE_SHIFT 12
#define PAGE_SIZE (1ul << PAGE_SHIFT)

#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)
#define SECTION_SIZE (1ul << SECTION_SHIFT)

#define LOW_MEMORY (2 * SECTION_SIZE)

#ifndef __ASSEMBLER__

#include <stdint.h>

void memzero(u64 src, u32 n);

#endif

#endif /* _ARCH_MM_MM_H */