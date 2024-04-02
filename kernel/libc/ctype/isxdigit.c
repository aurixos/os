#include <ctype.h>

int isxdigit(int c)
{
	return _Ctype[c] & (_XD);
}
