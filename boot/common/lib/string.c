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

#include <stdint.h>
#include <stddef.h>

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
    size_t count;

    if (str == NULL) {
        return 0;
    }

    do {
        count++;
    } while (str[count] != '\0');

    return count;
}

