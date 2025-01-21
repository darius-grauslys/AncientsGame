#ifndef BITMAP_H
#define BITMAP_H

#include "debug/debug.h"
#include "defines_weak.h"

#define BITMAP(name, N)\
    u8 name[ N >> 3];

void initialize_bitmap(
        u8 *p_bitmap,
        Quantity__u32 size_of__bitmap);

static inline
bool is_bit_set_in__bitmap(
        u8 *p_bitmap,
        Quantity__u32 size_of__bitmap,
        Index__u32 index_of__bit) {
#ifndef NDEBUG
    if (index_of__bit >= size_of__bitmap) {
        debug_error("is_bit_set_in__bitmap, index out of bounds %d/%d",
                index_of__bit,
                size_of__bitmap);
        return false;
    }
#endif
    return BIT(index_of__bit & MASK(3))
        & p_bitmap[index_of__bit >> 3];
}

static inline
void set_bit_in__bitmap(
        u8 *p_bitmap,
        Quantity__u32 size_of__bitmap,
        Index__u32 index_of__bit,
        bool state_of__bit) {
#ifndef NDEBUG
    if (index_of__bit >= size_of__bitmap) {
        debug_error("set_bit_in__bitmap, index out of bounds %d/%d",
                index_of__bit,
                size_of__bitmap);
        return;
    }
#endif
    p_bitmap[index_of__bit >> 3] 
        = 
        (state_of__bit)
        ? BIT(index_of__bit & MASK(3)) | p_bitmap[index_of__bit >> 3]
        : (~BIT(index_of__bit & MASK(3))) & p_bitmap[index_of__bit >> 3]
        ;
}

#endif
