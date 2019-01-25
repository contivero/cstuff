#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

/* Loosely based on Eric S. Roberts' characteristic vectors
 * Set union, intersection, difference and complement are also implemented.
 */

#define RANGE_SIZE      255
#define BITS_PER_BYTE   8
#define BITS_PER_UL     (BITS_PER_BYTE * sizeof(unsigned long))
#define WORDS           ((RANGE_SIZE + BITS_PER_UL + 1)/BITS_PER_UL)

typedef struct Bitmap {
    unsigned long bitmap[WORDS];
} Bitmap;

Bitmap *
newbitmap(void) {
    Bitmap *bm = xmalloc(sizeof(*bm));

    return bm;
}

inline unsigned long
mask(size_t k) {
    return (unsigned long) 1 << (k % BITS_PER_UL);
}

bool
bitmaptest(Bitmap *bm, size_t k) {
    if (k >= RANGE_SIZE)
        die("error: outside of range");

    return bm->bitmap[k/BITS_PER_UL] & mask(k);
}

Bitmap *
bitmapunion(const Bitmap *bm1, const Bitmap *bm2) {
    Bitmap *ret = newbitmap();

    for (size_t i = 0; i < WORDS; i++)
        ret->bitmap[i] = bm1->bitmap[i] | bm2->bitmap[i];

    return ret;
}

Bitmap *
bitmapintersection(const Bitmap *bm1, const Bitmap *bm2) {
    Bitmap *ret = newbitmap();

    for (size_t i = 0; i < WORDS; i++)
        ret->bitmap[i] = bm1->bitmap[i] & bm2->bitmap[i];

    return ret;
}

Bitmap *
bitmapdifference(const Bitmap *bm1, const Bitmap *bm2) {
    Bitmap *ret = newbitmap();

    for (size_t i = 0; i < WORDS; i++)
        ret->bitmap[i] = bm1->bitmap[i] & (~bm2->bitmap[i]);

    return ret;
}

Bitmap *
bitmapcomplement(const Bitmap *bm1) {
    Bitmap *ret = newbitmap();

    for (size_t i = 0; i < WORDS; i++)
        ret->bitmap[i] = ~bm1->bitmap[i];

    return ret;
}
