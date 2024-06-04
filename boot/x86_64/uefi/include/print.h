#ifndef _PRINT_H
#define _PRINT_H

#include <efi.h>

VOID
EfiOutputString(CHAR16 *String);

VOID
EfiPrint(CHAR16 *Format, ...);

VOID
EfiPrintDebug(CHAR16 *Format, ...);

VOID
pEfiPrintFormat(VOID (*Callback)(CHAR16 *), CHAR16 *Format, VA_LIST Args);

INT32
pEfiPrintInteger(VOID (*Callback)(CHAR16 *), UINTN Number, UINT8 Base, BOOLEAN IsSigned);

#endif /* _PRINT_H */