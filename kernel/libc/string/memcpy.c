#include <stdint.h>
#include <string.h>

void *memcpy(void *s1, const void * s2, size_t n)
{
	char *su1;
	const char *su2;

	for (su1 = s1, su2 = s2; n > 0; ++su1, ++su2, --n) {
		*su1 = *su2;
	}

	return s1;
}