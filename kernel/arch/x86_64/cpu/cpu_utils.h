#ifndef _ARCH_CPU_UTILS_H
#define _ARCH_CPU_UTILS_H

#include <stdint.h>

////
// CPU-Related instructions
///
static inline void cpuid(int code, uint32_t *a, uint32_t *d)
{
    __asm__ volatile( "cpuid"
					: "=a"(*a), "=d"(*d)
					: "0"(code)
					: "ebx", "ecx");
}

static inline uint64_t rdtsc(void)
{
    uint32_t lo;
    uint32_t hi;
    __asm__ volatile("rdtsc"
					: "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

static inline void invlpg(void *tlb)
{
	__asm__ volatile("invlpg (%0)"
					:: "b"(tlb)
					: "memory");
}

////
// Model Specific Registers
///

static inline uint64_t rdmsr(uint64_t msr)
{
	uint32_t lo;
	uint32_t hi;
	__asm__ volatile("rdmsr"
					: "=a"(lo), "=d"(hi)
					: "c"(msr));
	return ((uint64_t)hi << 32) | lo;
}

static inline void wrmsr(uint64_t msr, uint64_t val)
{
	uint32_t lo = val & 0xFFFFFFFF;
	uint32_t hi = val >> 32;
	__asm__ volatile("wrmsr"
					:: "c"(msr), "a"(lo), "d"(hi));
}

////
// Reading Control Registers
///
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

#endif /* _ARCH_CPU_UTILS_H */
