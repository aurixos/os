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
	UINT16 Size;
#if defined (__i686__)
	UINT Base;
#elif defined (__amd64__)
	UINT64 Base;
#endif
} PACKED KGDT_DESCRIPTOR, *PKGDT_DESCRIPTOR;

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
pHalLoadGdt(PKGDT_DESCRIPTOR Descriptor);

#endif /* _HAL_X86_CPU_H */
