#ifndef __AXBOOT_H
#define __AXBOOT_H

#include <efi.h>

extern EFI_HANDLE g_ImageHandle;
extern EFI_SYSTEM_TABLE *g_SystemTable;

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

#define BOOTLOADER_NAME L"AxBoot"
#define BOOTLOADER_VER_STR L"0.1"
#define BOOTLOADER_COPYRIGHT_STR L"Copyright (c) 2023-2024 AurixOS"

EFI_STATUS
AxBootEntryPoint(EFI_HANDLE ImageHandle,
				 EFI_SYSTEM_TABLE *SystemTable);

#endif /* __AXBOOT_H */
