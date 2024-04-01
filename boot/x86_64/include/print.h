#ifndef __PRINT_H
#define __PRINT_H

VOID
EfiPrint(CHAR16 *Format, ...);

INT32
EfiPrintInteger(UINTN Number, UINT8 Base, BOOLEAN IsSigned);

#endif /* __PRINT_H */
