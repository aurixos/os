/*++
Module Name:  init.c
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

#include <hal/cpu.h>
#include <aurix.h>

void
HalEarlyInitCpu()
{
	pHalInitGdt();
	pHalInitIdt();
}

void
pHalInitGdt()
{
	ALIGNED(0x1000) KGDT_ENTRY GdtEntries[5];
	KGDT_DESCRIPTOR GdtDescriptor;

	//
	// NULL
	//
	pHalSetGdtEntry(&GdtEntries[0], 0, 0, 0, 0);

#if defined (__i686__)
	//
	// 32-bit Kernel Code
	//
	pHalSetGdtEntry(&GdtEntries[1], 0, 0xFFFFF, 0x9A, 0xC);

	//
	// 32-bit Kernel Data
	//
	pHalSetGdtEntry(&GdtEntries[2], 0, 0xFFFFF, 0x92, 0xC);

	//
	// 32-bit User Code
	//
	pHalSetGdtEntry(&GdtEntries[3], 0, 0xFFFFF, 0xFA, 0xC);

	//
	// 32-bit User Data
	//
	pHalSetGdtEntry(&GdtEntries[4], 0, 0xFFFFF, 0xF2, 0xC);
#else
	//
	// 64-bit Kernel Code
	//
	pHalSetGdtEntry(&GdtEntries[1], 0, 0, 0x9A, 0xA);

	//
	// 64-bit Kernel Data
	//
	pHalSetGdtEntry(&GdtEntries[2], 0, 0, 0x92, 0xC);

	//
	// 64-bit User Code
	//
	pHalSetGdtEntry(&GdtEntries[3], 0, 0, 0xFA, 0xA);

	//
	// 64-bit User Data
	//
	pHalSetGdtEntry(&GdtEntries[4], 0, 0, 0xF2, 0xC);
#endif

	GdtDescriptor.Size = sizeof(GdtEntries) - 1;
#if defined (__i686__)
	GdtDescriptor.Base = (UINT)&GdtEntries;
#elif defined (__amd64__)
	GdtDescriptor.Base = (ULONG)&GdtEntries;
#endif

	pHalLoadGdt(&GdtDescriptor);
}

void
pHalSetGdtEntry(PKGDT_ENTRY Entry,
				UINT32 Base,
				UINT32 Limit,
				UINT8 Access,
				UINT8 Flags)
{
	Entry->LimitLower = (Limit >> 8) & 0xFFFF;
	Entry->BaseLower = (Base >> 8) & 0xFFFF;
	Entry->BaseMiddle = (Base >> 16) & 0xFF;
	Entry->Access = Access;
	Entry->LimitHigher = (Limit >> 16) & 0xF;
	Entry->Flags = Flags;
	Entry->BaseHigher = (Base >> 24) & 0xFF;
}

void
pHalInitIdt()
{
	ALIGNED(0x1000) KIDT_ENTRY IdtEntries[256];
	KIDT_DESCRIPTOR IdtDescriptor;

	//
	// Set up exception handlers
	//
	for(INT Index = 0; Index < 32; Index++)
	{
		pHalSetIdtEntry(&IdtEntries[Index], pgHalIsrHandlers[Index], IDT_TRAP_GATE);
	}

	//
	// Set up ISR handlers
	//
	for(INT Index = 32; Index < 256; Index++)
	{
		pHalSetIdtEntry(&IdtEntries[Index], pgHalIsrHandlers[Index], IDT_INTERRUPT_GATE);
	}

	IdtDescriptor.Size = sizeof(IdtEntries) - 1;
#if defined (__i686__)
	IdtDescriptor.Base = (UINT)&IdtEntries;
#elif defined (__amd64__)
	IdtDescriptor.Base = (ULONG)&IdtEntries;
#endif

	pHalLoadIdt(&IdtDescriptor);
}

void
pHalSetIdtEntry(PKIDT_ENTRY Entry,
				PVOID Handler,
				UINT8 Flags)
{
	Entry->Reserved = 0;

#if defined (__i686__)
	Entry->BaseLower = ((UINT32)Handler) & 0xFFFF;
	Entry->Selector = 0x08;
	Entry->Flags = Flags;
	Entry->BaseHigher = (((UINT32)Handler) >> 16) & 0xFFFF;
#elif defined (__amd64__)
	Entry->BaseLower = ((UINT64)Handler) & 0xFFFF;
	Entry->Selector = 0x08;
	Entry->Ist = 0;
	Entry->Flags = Flags;
	Entry->BaseMiddle = (((UINT64)Handler) >> 16) & 0xFFFF;
	Entry->BaseHigher = ((UINT64)Handler) >> 32;
#endif
}
