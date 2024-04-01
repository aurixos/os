#include <efi_types.h>

CHAR16 *
WideStringCopy(CHAR16 *Destination, CHAR16 *Source)
{
	if (!Destination) {
		return NULL;
	}
	if (!Source) {
		return Destination;
	}

	CHAR16 *Result = Destination;
	while (*Source) {
		*Destination++ = *Source++;
	}

	*Destination = L'\0';
	return Result;
}
