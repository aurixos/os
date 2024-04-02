#include <ctype.h>

// TODO: fix this
// #include <limits.h>
// #include <stdio.h>
#define EOF -1
#define UCHAR_MAX 255

#if EOF != -1 || UCHAR_MAX != 255
# error "Wrong ctype table!"
#endif

#define XDI (_DI | _XD)
#define XLO (_LO | _XD)
#define XUP (_UP | _XD)

static const short ctype_tab[257] = {0, /* EOF */
_BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
_CN, _CN, _CN, _CN, _CN, _CN, _BB, _BB,
_BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
_BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
_SP, _PU, _PU, _PU, _PU, _PU, _PU, _PU,
_PU, _PU, _PU, _PU, _PU, _PU, _PU, _PU,
XDI, XDI, XDI, XDI, XDI, XDI, XDI, XDI,
XDI, XDI, _PU, _PU, _PU, _PU, _PU, _PU,
_PU, XUP, XUP, XUP, XUP, XUP, XUP, _UP,
_UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,
_UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,
_UP, _UP, _UP, _PU, _PU, _PU, _PU, _PU,
_PU, XLO, XLO, XLO, XLO, XLO, XLO, _LO,
_LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,
_LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,
_LO, _LO, _LO, _PU, _PU, _PU, _PU, _BB,
};

const short *_Ctype = &ctype_tab[1];
