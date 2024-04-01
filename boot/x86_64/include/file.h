#ifndef __FILE_H
#define __FILE_H

#include <efi.h>

VOID *
FileRead(CHAR16 *Filename, UINTN *FileSize);

#endif /* __FILE_H */
