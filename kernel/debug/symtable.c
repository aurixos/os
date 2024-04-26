#include <debug/symtable.h>

// allow this to be overridden
__attribute__((weak))
const struct symbol _symtab[] = {
	{UINTPTR_MAX, ""}
};
