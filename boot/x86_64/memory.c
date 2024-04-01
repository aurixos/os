#include <efi.h>

VOID *
MemCopy(VOID *Dest, CONST VOID *Source, SIZE Size)
{
	UINT8 *DestPtr = (UINT8 *)Dest;
	UINT8 *SourcePtr = (UINT8 *)Source;

	for (SIZE Index = 0; Index < Size; Index++) {
		DestPtr[Index] = SourcePtr[Index];
	}

	return Dest;
}

VOID *
MemSet(VOID *Dest, INT32 Byte, SIZE Size)
{
	UINT8 *Ptr = (UINT8 *)Dest;

	for (SIZE Index = 0; Index < Size; Index++) {
		Ptr[Index] = (UINT8)Byte;
	}

	return Dest;
}

VOID *
MemMove(VOID *Dest, CONST VOID *Source, SIZE Size)
{
	UINT8 *DestPtr = (UINT8 *)Dest;
	UINT8 *SourcePtr = (UINT8 *)Source;

	if (Source > Dest) {
		for (SIZE Index = 0; Index < Size; Index++) {
			DestPtr[Index] = SourcePtr[Index];
		}
	} else if (Source < Dest) {
		for (SIZE Index = Size; Index > 0; Index--) {
			DestPtr[Index - 1] = SourcePtr[Index - 1];
		}
	}

	return Dest;
}

INT32 MemCompare(CONST VOID *S1, CONST VOID *S2, SIZE Size)
{
	const UINT8 *Ptr1 = (const UINT8 *)S1;
    const UINT8 *Ptr2 = (const UINT8 *)S2;

	for (SIZE Index = 0; Index < Size; Index++) {
        if (Ptr1[Index] != Ptr2[Index]) {
            return Ptr1[Index] < Ptr2[Index] ? -1 : 1;
        }
    }

	return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    return MemCopy(dest, src, n);
}

void *memset(void *s, int c, size_t n)
{
	return MemSet(s, c, n);
}

void *memmove(void *dest, const void *src, size_t n)
{
    return MemMove(dest, src, n);
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    return MemCompare(s1, s2, n);
}
