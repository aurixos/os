#ifndef __FILE_H
#define __FILE_H

#include <efi.h>

EFI_FILE_PROTOCOL *
FileOpen(CHAR16 *Filename, UINTN *FileSize);

VOID
FileClose(EFI_FILE_PROTOCOL *File);

#endif /* __FILE_H */
