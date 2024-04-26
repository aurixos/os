#ifndef _DEBUG_SYMTABLE_H
#define _DEBUG_SYMTABLE_H

#include <stdint.h>

struct symbol {
	uintptr_t addr;
	char *name;
};

extern const struct symbol _symtab[];

#endif /* _DEBUG_SYMTABLE_H */
