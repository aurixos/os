#ifndef PRINT_H
#define PRINT_H

VOID
EfiPrint(CHAR16 *Format, ...);

INT32
EfiPrintInteger(UINTN Number, UINT8 Base, BOOLEAN IsSigned);

#endif /* PRINT_H */
