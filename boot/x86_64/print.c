#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>

INTN
EfiPrint(CHAR16 *Format, ...)
{
	VA_LIST Args;
	INTN Counter;
	CHAR16 CharString[2];

	va_start(Args, Format);
	Counter = 0;
	CharString[0] = L'\0';
	CharString[1] = L'\0';

	for (UINTN i = 0; Format[i] != L'\0'; i++) {
		if (Format[i] == L'%') {
			i++;

			if (Format[i] == L'c') {
				CharString[0] = va_arg(Args, int);
				g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, CharString);
				Counter++;
			} else {
				g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, L"%?");
				Counter += 2;
			}
		} else {
			CharString[0] = Format[i];
			g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, CharString);
			Counter++;
		}
	}

	va_end(Args);

	return Counter;
}
