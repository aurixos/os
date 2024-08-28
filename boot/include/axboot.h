/*********************************************************************************/
/* Module Name:  axboot.h                                                        */
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

#ifndef _AXBOOT_H
#define _AXBOOT_H

#define HIGHER_HALF 0xffffffff80000000

#define PHYS_TO_VIRT(addr) ((uint64_t)(addr) + HIGHER_HALF)
#define VIRT_TO_PHYS(addr) ((uint64_t)(addr) - HIGHER_HALF)

#define ARRAY_LENGTH(x) ((sizeof(x)) / (sizeof((x[0]))))

#define ROUND_DOWN(x, a) (((x)) & (~((a) - 1)))
#define ROUND_UP(x, a) ((((x)) + (a) - 1) & (~((a) - 1)) ) 

#define BOOTLOADER_NAME_STR "AxBoot"
#define BOOTLOADER_VERSION_STR "0.1"

#ifndef UNREACHABLE
	#define UNREACHABLE()
#endif

#endif /* _AXBOOT_H */