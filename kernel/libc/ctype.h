#ifndef _CTYPE_H
#define _CTYPE_H

/* _Ctype code bits */
#define _XA 0x200 /* extra alphabetic */
#define _XS 0x100 /* extra space */
#define _BB 0x80 /* BEL, BS, etc. */
#define _CN 0x40 /* CR, FF, HT, NL, VT */
#define _DI 0x20 /* '0' - '9' */
#define _LO 0x10 /* 'a' - 'z' */
#define _PU 0x08 /* punctuation */
#define _SP 0x04 /* space */
#define _UP 0x02 /* 'A' - 'Z' */
#define _XD 0x01 /* '0' - '9', 'A' - F', 'a' - 'f' */

int isalnum(int);
int isalpha(int);
// int iscntrl(int);
// int isdigit(int);
// int isgraph(int);
// int islower(int);
// int isprint(int);
int ispunct(int);
int isspace(int);
// int isupper(int);
int isxdigit(int);

// int tolower(int);
// int toupper(int);

extern const short *_Ctype;

#endif