#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>

VOID
EfiPrint(CHAR16 *Format, ...)
{
	VA_LIST Args;
	CHAR16 CharString[2];

	va_start(Args, Format);
	CharString[0] = L'\0';
	CharString[1] = L'\0';

	for (UINTN i = 0; Format[i] != L'\0'; i++) {
		if (Format[i] == L'%') {
			i++;

			if (Format[i] == L'c') {
				CharString[0] = va_arg(Args, int);
				g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, CharString);
			} else if (Format[i] == L's') {
				CHAR16 *String = va_arg(Args, CHAR16 *);
				g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, String);
			} else {
				g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, L"%?");
			}
		} else {
			CharString[0] = Format[i];
			g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, CharString);
		}
	}

	va_end(Args);
}
