#include <ctype.h>

int isalpha(int c)
{
	return (_Ctype[c] & (_LO | _UP));
}
