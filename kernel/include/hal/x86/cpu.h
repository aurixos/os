/*++
Module Name:  cpu.h
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

#ifndef _HAL_X86_CPU_H
#define _HAL_X86_CPU_H

#include <aurix.h>

//// ** MACROS ** ////

//
// IDT Types
//
#define IDT_INTERRUPT_GATE			0x8E
#define IDT_TRAP_GATE				0x8F

//// ** STRUCTURES ** ////

//
// GDT Entry
//
typedef struct _KGDT_ENTRY
{
	UINT16 LimitLower;
	UINT16 BaseLower;
	UINT8 BaseMiddle;
	UINT8 Access;
	UINT8 LimitHigher : 4;
	UINT8 Flags : 4;
	UINT8 BaseHigher;
} PACKED KGDT_ENTRY, *PKGDT_ENTRY;

//
// GDT Descriptor
//
typedef struct _KGDT_DESCRIPTOR
{
	USHORT Size;
#if defined (__i686__)
	UINT Base;
#elif defined (__amd64__)
	ULONG Base;
#endif
} PACKED KGDT_DESCRIPTOR, *PKGDT_DESCRIPTOR;

//
// IDT Entry
//
typedef struct _KIDT_ENTRY
{
#if defined (__i686__)
	UINT16 BaseLower;
	UINT16 Selector;
	UINT8 Reserved;
	UINT8 Flags;
	UINT16 BaseHigher;
#elif defined (__amd64__)
	UINT16 BaseLower;
	UINT16 Selector;
	UINT8 Ist;
	UINT8 Flags;
	UINT16 BaseMiddle;
	UINT32 BaseHigher;
	UINT32 Reserved;
#endif
} PACKED KIDT_ENTRY, *PKIDT_ENTRY;

//
// IDT Descriptor
//
typedef struct _KIDT_DESCRIPTOR
{
	USHORT Size;
#if defined (__i686__)
	UINT Base;
#elif defined (__amd64__)
	ULONG Base;
#endif
} PACKED KIDT_DESCRIPTOR, *PKIDT_DESCRIPTOR;

//// ** EXTERN VARIABLES ** ////

EXTERN PVOID pgHalIsrHandlers[];

//// ** INITIALIZATION ** ////

void pHalInitGdt();
void pHalInitIdt();

//// ** PRIVATE FUNCTIONS ** ////

void
pHalSetGdtEntry(PKGDT_ENTRY Entry,
				UINT32 Base,
				UINT32 Limit,
				UINT8 Access,
				UINT8 Flags);

void
pHalSetIdtEntry(PKIDT_ENTRY Entry,
				PVOID Handler,
				UINT8 Flags);

EXTERN
void
pHalLoadGdt(PKGDT_DESCRIPTOR Descriptor);

EXTERN
void
pHalLoadIdt(PKIDT_DESCRIPTOR Descriptor);

#endif /* _HAL_X86_CPU_H */
