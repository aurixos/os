#ifndef _DATA_BMAP_H
#define _DATA_BMAP_H

#include <stdint.h>
#include <stddef.h>

typedef struct bitmap
{
    uint32_t *map;
    size_t size;
} bitmap_t;

void bitmap_set(bitmap_t *bitmap, int bit);
void bitmap_clear(bitmap_t *bitmap, int bit);
uint32_t bitmap_get(bitmap_t *bitmap, int bit);

#endif /* _DATA_BMAP_H */
