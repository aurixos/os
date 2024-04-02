#include <ctype.h>

int isalnum(int c)
{
	return (_Ctype[c] & (_LO|_UP|_XA));
}
