/*++
Module Name:  aurixos.h
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

#ifndef _AURIXOS_H
#define _AURIXOS_H

#include <axtypes.h>
#include <axdef.h>

//
// Calculates the size of an array
//
#define ARRAY_SIZE(Array) (sizeof(Array) / sizeof(Array[0]))

//
// Rounds a number up
//
#define ROUND_UP(Value, Align) (((Value) + (Align - 1), Align) & ~((Align) - 1))

//
// Rounds a number down
//
#define ROUND_DOWN(Value, Align) ((Value) & ~((Align) - 1))

//
// Creates a string out of input text
//
#define __priv___STRINGIZE(x...) #x
#define STRINGIZE(x...) __priv___STRINGIZE(x)

#endif /* _AURIXOS_H */
