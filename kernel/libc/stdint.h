#ifndef _STDINT_H
#define _STDINT_H

#include <aurix.h>
#include ARCH_INCLUDE(sys/_types.h)

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

typedef size_t usize;
typedef ssize_t isize;

typedef volatile uint32_t reg32;

#endif /* _STDINT_H */