#ifndef _MM_MMIO_H
#define _MM_MMIO_H

#include <stdint.h>

uint32_t mmio_read(long addr);
void mmio_write(long addr, uint32_t val);

#endif /* _MM_MMIO_H */
