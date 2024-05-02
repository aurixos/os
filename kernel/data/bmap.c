#include <data/bmap.h>

void bitmap_set(bitmap_t *bitmap, int bit)
{
    bitmap->map[bit / 32] |= (1 << (bit % 32));
}

void bitmap_clear(bitmap_t *bitmap, int bit)
{
    bitmap->map[bit / 32] &= ~(1 << (bit % 32));
}

uint8_t bitmap_get(bitmap_t *bitmap, int bit)
{
    return bitmap->map[bit / 32] & (1 << (bit % 32));
}
