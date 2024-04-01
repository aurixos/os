#include <efi.h>
#include <efilib.h>

#include <axboot.h>
#include <print.h>

// Modified version of Queso Fuego's printf() implementation
// https://github.com/queso-fuego/uefi-dev/blob/main/efi_c/efi.c
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
			} else if (Format[i] == L'd') {
				INT32 Number = va_arg(Args, INT32);
				EfiPrintInteger(Number, 10, TRUE);
			} else if (Format[i] == L'x') {
				UINTN Number = va_arg(Args, UINTN);
				EfiPrintInteger(Number, 16, FALSE);
			} else if (Format[i] == L'u') {
				UINT32 Number = va_arg(Args, UINT32);
				EfiPrintInteger(Number, 10, FALSE);
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

INT32
EfiPrintInteger(UINTN Number, UINT8 Base, BOOLEAN IsSigned)
{
	const CHAR16 *Digits = L"0123456789ABCDEF";
	CHAR16 Buffer[24];
	UINTN i = 0;
	INT32 RetVal = 0;
	BOOLEAN IsNegative = FALSE;

	if (Base > 16) {
		return -1;
	}

	if (Base == 10 && IsSigned && (INTN)Number < 0) {
		Number = -(INTN)Number;
		IsNegative = TRUE;
	}

	do {
		Buffer[i++] = Digits[Number % Base];
		Number /= Base;
	} while (Number > 0);

	if (Base == 10 && IsNegative) {
		Buffer[i++] = L'-';
	}

	Buffer[i--] = L'\0';

	RetVal = i;

	// Reverse string
	for (UINTN j = 0; j < i; j++, i--) {
		UINTN Temp = Buffer[i];
		Buffer[i] = Buffer[j];
		Buffer[j] = Temp;
	}

	g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, Buffer);
	return RetVal;
}
