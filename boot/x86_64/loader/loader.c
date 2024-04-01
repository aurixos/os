#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <config.h>
#include <print.h>

#include <loader/loader.h>
#include <loader/aurix.h>
#include <loader/elf.h>

VOID
LoaderBootEntry(struct BootEntry *Entry)
{
	switch (Entry->Protocol) {
		case ENTRY_PROTOCOL_CHAINLOAD: {
			// LoaderChainload(Entry);
			break;
		}
		case ENTRY_PROTOCOL_AURIX: {
			LoaderAurixBoot(Entry);
			break;
		}
		default: {
			EfiPrint(L"Unknown protocol type!\r\n");
			break;
		}
	}
}
