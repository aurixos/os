#include <data/bmap.h>

__attribute__((always_inline))
inline void bitmap_set(bitmap_t *bitmap, int bit)
{
    bitmap->map[bit / 32] |= (1 << (bit % 32));
}

__attribute__((always_inline))
inline void bitmap_clear(bitmap_t *bitmap, int bit)
{
    bitmap->map[bit / 32] &= ~(1 << (bit % 32));
}

__attribute__((always_inline))
inline uint32_t bitmap_get(bitmap_t *bitmap, int bit)
{
    return bitmap->map[bit / 32] & (1 << (bit % 32));
}
