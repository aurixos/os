#ifndef _ARCH_SYS_TYPES_H
#define _ARCH_SYS_TYPES_H

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;

typedef unsigned long size_t;
typedef long ssize_t;

typedef long ptrdiff_t;

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

typedef unsigned long uintptr_t;

#define	UINTPTR_MAX 0xfffffffffffffffful

#endif /* _ARCH_SYS_TYPES_H */