/*********************************************************************************/
/* Module Name:  print.c                                                         */
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

#include <print.h>

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

int log(const char *fmt, ...)
{
	va_list args;
	int ret;

	va_start(args, fmt);
	ret = vfprintf(printstr, fmt, args);
	va_end(args);

	return ret;
}

int debug(const char *fmt, ...)
{
	va_list args;
	int ret;

	va_start(args, fmt);
	//ret = vfprintf(debug_printstr, fmt, args);
	ret = vfprintf(printstr, fmt, args);
	va_end(args);

	return ret;
}

int vfprintf(void (*print_callback)(const char *), const char *fmt, va_list args)
{
	size_t i;

	for (i = 0; fmt[i] != '\0'; i++) {
		if (fmt[i] == '%') {
			i++;
			switch (fmt[i]) {
				case 'c': {
					char c = va_arg(args, int);
					print_callback(&c);
					break;
				}
				case 's': {
					char *s = va_arg(args, char *);
					print_callback(s);
					break;
				}
				case 'd': {
					int32_t n = va_arg(args, int32_t);
					_print_num(print_callback, n, 10, true);
					break;
				}
				case 'u': {
					uint32_t n = va_arg(args, uint32_t);
					_print_num(print_callback, n, 10, false);
					break;
				}
				case 'b': {
					uint64_t n = va_arg(args, uint64_t);
					_print_num(print_callback, n, 2, false);
					break;
				}
				case 'o': {
					uint64_t n = va_arg(args, uint64_t);
					_print_num(print_callback, n, 8, false);
					break;
				}
				case 'x': {
					uint64_t n = va_arg(args, uint64_t);
					_print_num(print_callback, n, 16, false);
					break;
				}
				default: {
					print_callback("%%?");
					break;
				}
			}
		} else {
			char s[2];
			s[0] = fmt[i];
			s[1] = '\0';
			print_callback(s);
		}
	}

	return i;
}

void _print_num(void (*print_callback)(const char *), uint64_t num, uint8_t base, bool is_signed)
{
	const char *digits = "0123456789abcdef";
	char buffer[24];
	size_t i = 0;
	bool negative = false;

	if (base > 16) {
		print_callback("%?");
		return;
	}

	if (base == 10 && is_signed && (int64_t)num < 0) {
		num = -(int64_t)num;
		negative = true;
	}

	do {
		buffer[i++] = digits[num % base];
		num /= base;
	} while (num > 0);

	if (base == 10 && negative) {
		buffer[i++] = '-';
	}

	buffer[i--] = '\0';

	for (size_t j = 0; j < i; j++, i--) {
		char temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
	}

	print_callback(buffer);
}