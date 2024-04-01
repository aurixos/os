#ifndef __LOADER_LOADER_H
#define __LOADER_LOADER_H

#include <config.h>

// entry protocols
enum {
	ENTRY_PROTOCOL_CHAINLOAD = 0,
	ENTRY_PROTOCOL_AURIX,
	ENTRY_PROTOCOL_MAX
};

VOID
LoaderBootEntry(struct BootEntry *Entry);

#endif /* __LOADER_LOADER_H */
