/*++
Module Name:  print.c
Project:      AurixOS

Copyright (c) 2024 Jozef Nagy

This source is subject to the MIT License.
See License.txt in the root of this repository.
All other rights reserved.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--*/

#include <axboot.h>
#include <efi.h>
#include <efilib.h>

#include <com.h>
#include <print.h>

VOID
EfiOutputString(CHAR16 *String)
{
	g_SystemTable->ConOut->OutputString(g_SystemTable->ConOut, String);
}

VOID
EfiPrint(CHAR16 *Format, ...)
{
	VA_LIST Args;
	va_start(Args, Format);
	pEfiPrintFormat(EfiOutputString, Format, Args);
	va_end(Args);
}

VOID
EfiPrintDebug(CHAR16 *Format, ...)
{
	VA_LIST Args;
	va_start(Args, Format);
	pEfiPrintFormat(ComOutputDebugString, Format, Args);
	va_end(Args);
}

VOID
pEfiPrintFormat(VOID (*Callback)(CHAR16 *), CHAR16 *Format, VA_LIST Args)
{
	CHAR16 CharString[2];

	CharString[0] = L'\0';
	CharString[1] = L'\0';

	for (UINTN i = 0; Format[i] != L'\0'; i++) {
		if (Format[i] == L'%') {
			i++;

			if (Format[i] == L'c') {
				CharString[0] = va_arg(Args, int);
				Callback(CharString);
			} else if (Format[i] == L's') {
				CHAR16 *String = va_arg(Args, CHAR16 *);
				Callback(String);
			} else if (Format[i] == L'd') {
				INT32 Number = va_arg(Args, INT32);
				pEfiPrintInteger(Callback, Number, 10, TRUE);
			} else if (Format[i] == L'x') {
				UINTN Number = va_arg(Args, UINTN);
				pEfiPrintInteger(Callback, Number, 16, FALSE);
			} else if (Format[i] == L'u') {
				UINT32 Number = va_arg(Args, UINT32);
				pEfiPrintInteger(Callback, Number, 10, FALSE);
			} else {
				Callback(L"%?");
			}
		} else {
			CharString[0] = Format[i];
			Callback(CharString);
		}
	}
}

INT32
pEfiPrintInteger(VOID (*Callback)(CHAR16 *), UINTN Number, UINT8 Base, BOOLEAN IsSigned)
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

	Callback(Buffer);
	return RetVal;
}