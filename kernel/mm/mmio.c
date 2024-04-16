#include <mm/mmio.h>

#include <stdint.h>

uint32_t mmio_read(long addr)
{
	return *((volatile uint32_t *)(addr));
}

void mmio_write(long addr, uint32_t val)
{
	(*((volatile uint32_t *)(addr))) = (val);
}
