#ifndef _PRINT_H
#define _PRINT_H

#include <efi.h>

VOID
EfiOutputString(CHAR16 *String);

VOID
EfiPrint(CHAR16 *Format, ...);

INT32
EfiPrintInteger(UINTN Number, UINT8 Base, BOOLEAN IsSigned);

#endif /* _PRINT_H */