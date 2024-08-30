/*********************************************************************************/
/* Module Name:  cpu.h                                                           */
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

#ifndef _ARCH_CPU_CPU_H
#define _ARCH_CPU_CPU_H

#include <stdint.h>

static inline void cpu_disable_interrupts(void)
{
	__asm__ volatile("cli" ::: "memory");
}

static inline uint64_t read_cr0()
{
	uint64_t val;
	__asm__ volatile("mov %%cr0, %0"
					: "=r"(val));
	return val;
}

static inline uint64_t read_cr2()
{
	uint64_t val;
	__asm__ volatile("mov %%cr2, %0"
					: "=r"(val));
	return val;
}

static inline uint64_t read_cr3()
{
	uint64_t val;
	__asm__ volatile("mov %%cr3, %0"
					: "=r"(val));
	return val;
}

static inline uint64_t read_cr4()
{
	uint64_t val;
	__asm__ volatile("mov %%cr4, %0"
					: "=r"(val));
	return val;
}

static inline uint64_t read_cr8()
{
	uint64_t val;
	__asm__ volatile("mov %%cr8, %0"
					: "=r"(val));
	return val;
}

////
// Writing Control Registers
///

static inline void write_cr0(uint64_t val)
{
	__asm__ volatile("mov %0, %%cr0"
					:: "r"(val));
}

static inline void write_cr2(uint64_t val)
{
	__asm__ volatile("mov %0, %%cr2"
					:: "r"(val));
}

static inline void write_cr3(uint64_t val)
{
	__asm__ volatile("mov %0, %%cr3"
					:: "r"(val) : "memory");
}

static inline void write_cr4(uint64_t val)
{
	__asm__ volatile("mov %0, %%cr4"
					:: "r"(val));
}

static inline void write_cr8(uint64_t val)
{
	__asm__ volatile("mov %0, %%cr8"
					:: "r"(val));
}

#endif /* _ARCH_CPU_CPU_H */