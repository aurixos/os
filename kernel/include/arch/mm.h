#ifndef _ARCH_MM_H
#define _ARCH_MM_H

#include <aurix.h>

#include ARCH_INCLUDE(mm/pmm.h)

#define BLOCKS_PER_LEVEL(level) (1 << (level))
#define SIZEOF_BLOCK_AT_LEVEL(level, total_size) ((total_size) / (1 << (level)))
#define INDEX_OF_POINTER_IN_LEVEL(ptr, level, memstart, total_size) (((ptr)-(memory_start)) / (SIZEOF_BLOCK_AT_LEVEL(level, total_size)))

#endif /* _ARCH_MM_H */
