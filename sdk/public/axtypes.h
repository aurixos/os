/*++
Module Name:  axtypes.h
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

#ifndef _AXTYPES_H
#define _AXTYPES_H

#if defined (_X32)
#define __int64 long long
#elif defined (_X64)
#define __int64 long
#endif

//
// Standard types
//
typedef signed char INT8, *PINT8;
typedef unsigned char UINT8, *PUINT8;
typedef signed short INT16, *PINT16;
typedef unsigned short UINT16, *PUINT16;
typedef signed int INT32, *PINT32;
typedef unsigned int UINT32, *PUINT32;
typedef __int64 INT64, *PINT64;
typedef unsigned __int64 UINT64, *PUINT64;

typedef void VOID, *PVOID;
typedef char CHAR, *PCHAR;
typedef signed short SHORT, *PSHORT;
typedef unsigned short USHORT, *PUSHORT;
typedef signed int INT, *PINT;
typedef unsigned int UINT, *PUINT;
typedef signed long INTN, *PINTN;
typedef unsigned long UINTN, *PUINTN;
typedef signed long LONG, *PLONG;
typedef unsigned long ULONG, *PULONG;
typedef signed long long LONGLONG, *PLONGLONG;
typedef unsigned long long ULONGLONG, *PULONGLONG;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;

//
// Boolean
//
typedef enum _BOOLEAN
{
	TRUE = 1,
	FALSE = 0
} BOOLEAN, *PBOOLEAN;

#endif /* _AXTYPES_H */
