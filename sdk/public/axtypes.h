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

#if defined(_X32)
#define __int64 long long
#elif defined(_X64)
#define __int64 long
#else
#error _X32/_X64 is not defined!
#endif

//
// Standard types
//
typedef char CHAR;

typedef   signed char INT8;
typedef unsigned char UINT8;
typedef   signed short INT16;
typedef unsigned short UINT16;
typedef   signed int INT32;
typedef unsigned int UINT32;
typedef   signed __int64 INT64;
typedef unsigned __int64 UINT64;

typedef signed int INT;
typedef unsigned UINT;

typedef   signed __int64 LONG;
typedef unsigned __int64 ULONG;

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
