/*********************************************************************************/
/* Module Name:  string.c                                                        */
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

#include <lib/string.h>
#include <firmware/memory.h>

#include <stdint.h>
#include <stddef.h>

void *malloc(size_t size)
{
	return fw_allocmem(size);
}

int mallocpage(size_t np, void *base)
{
	return fw_allocpage(np, base);
}

void free(void *p)
{
	fw_free(p);
}

size_t mbstowcs(wchar_t *dest, const char **src, size_t len)
{
	char *lsrc = (char *)*src;
	size_t count = len;

	if (dest == NULL) {
		return 0;
	}

	while (count) {
		if ((*dest = *lsrc) == 0) {
			lsrc = NULL;
			break;
		}

		if (*dest >= 0x80) {
			return -1;
		}

		lsrc++;
		dest++;
		count--;
	}

	return len - count;
}

size_t strlen(const char *str)
{
	size_t count = 0;

	if (str == NULL) {
		return 0;
	}

	do {
		count++;
	} while (str[count] != '\0');

	return count;
}

char *strcpy(char *dest, const char *src)
{
	if (dest == NULL || src == NULL) {
		return NULL;
	}

	char *pdest = dest;

	while (*src != '\0') {
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return pdest;
}

void *memset(void *dest, int val, size_t len)
{
	unsigned char *ptr = dest;
	while (len-- > 0) {
		*ptr++ = (unsigned char)val;
	}
	return dest;
}

void *memcpy(void *dest, void *src, size_t len)
{
	char *d = (char *)dest;
	const char *s = (const char *)src;

	while (len-- > 0) {
		*d++ = *s++;
	}

	return dest;
}

int memcmp(const void *a, const void *b, size_t len)
{
	unsigned char *ap = (unsigned char *)a;
    unsigned char *bp = (unsigned char *)b;
    int ret = 0;

    if (a == b) {
        return 0;
    }

    while (len > 0) {
        if (*ap != *bp) {
            ret = (*ap > *bp) ? 1 : -1;
            break;
        }

        len--;
        ap++;
        bp++;
    }

    return ret;
}