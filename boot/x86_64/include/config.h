#ifndef __CONFIG_H
#define __CONFIG_H

#include <efi.h>

struct BootModule {
	CHAR16 *Name;
	CHAR16 *ModulePath;
};

struct BootEntry {
	CHAR16 *Name;
	CHAR16 *KernelPath;
	CHAR16 *Cmdline;
	UINTN Protocol;

	struct BootModule *Modules;
	UINTN ModuleCount;
};

#endif /* __CONFIG_H */
