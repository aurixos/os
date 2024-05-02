#include <stdint.h>
#include <string.h>

void *memset(void *ptr, int c, size_t n)
{
	uint8_t *bufptr = (uint8_t *)ptr;

	for (size_t i = 0; i < n; i++) {
		bufptr[i] = c;
	}

	return ptr;
}
