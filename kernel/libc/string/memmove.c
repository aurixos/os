#include <stdint.h>
#include <string.h>

void *memmove(void *s1, const void *s2, size_t n)
{
	char *sc1;
	const char *sc2;

	sc1 = s1;
	sc2 = s2;
	if (sc2 < sc1 && sc1 < sc2 + n) {
		for (sc1 += n, sc2 += n; n > 0; --n) {
			*--sc1 = *--sc2;
		}
	} else {
		for (; n > 0; --n) {
			*sc1++ = *sc2++;
		}
	}

	return s1;
}