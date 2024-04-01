#ifndef __AXBOOT_H
#define __AXBOOT_H

#include <efi.h>

extern EFI_HANDLE g_ImageHandle;
extern EFI_SYSTEM_TABLE *g_SystemTable;

EFI_STATUS
AxBootEntryPoint(EFI_HANDLE ImageHandle,
				 EFI_SYSTEM_TABLE *SystemTable);

#endif /* __AXBOOT_H */
