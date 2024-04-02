#include <ctype.h>

int ispunct(int c)
{
	return _Ctype[c] & _PU;
}
