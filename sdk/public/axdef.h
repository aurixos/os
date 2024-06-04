/*++
Module Name:  axdef.h
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

#ifndef _AXDEF_H
#define _AXDEF_H

//
// Calling conventions
//
#define AXAPI __stdcall
#define CDECL __cdecl
#define FASTCALL __fastcall
#define CALLBACK __stdcall

//
// Variable modifiers
//
#define CONST const
#define EXTERN extern
#define STATIC static
#define VOLATILE volatile

//
// NULL (...self-explanatory)
//
#define NULL ((VOID*)0)

//
// Compiler attributes
//
#define PACKED __attribute__((packed))
#define ALIGNED(Align) __attribute__((aligned(Align)))
#define SECTION(Section) __attribute__((section(Section)))
#define NORETURN __attribute__((noreturn))

#endif /* _AXDEF_H */
