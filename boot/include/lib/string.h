/*********************************************************************************/
/* Module Name:  string.h                                                        */
/* Project:      AurixOS                                                         */
/*                                                                               */
/* Copyright (c) 2024 Jozef Nagy                                                 */
/*                                                                               */
/* This source is subject to the MIT License.                                    */
/* See License.txt in the root of this repository.                               */
/* All other rights reserved.                                                    */
/*                                                                               */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE.                                                                     */
/*********************************************************************************/

#ifndef _LIB_STRING_H
#define _LIB_STRING_H

#include <stddef.h>

//* FIRMWARE SPECIFIC *//

void *malloc(size_t n);
int mallocpage(size_t np, void *base);
void free(void *p);

//! FIRMWARE SPECIFIC !//

size_t mbstowcs(wchar_t *dest, const char **src, size_t len);

size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);

void *memset(void *dest, int val, size_t len);
void *memcpy(void *dest, void *src, size_t len);
int memcmp(const void *a, const void *b, size_t len);

#endif /* _LIB_STRING_H */