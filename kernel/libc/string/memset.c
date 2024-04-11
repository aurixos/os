#include <stdint.h>
#include <string.h>

void *memset(void *s, int c, size_t n)
{
	const unsigned char uc = c;
	unsigned char *su;

	for (su = s; n > 0; ++su, --n) {
		*su = uc;
	}

	return s;
}
