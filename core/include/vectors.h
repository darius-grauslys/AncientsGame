#ifndef VECTORS_H
#define VECTORS_H

/// This file includes all static inline helpers
/// to deal with vectors.

#include <defines.h>

static void inline init_3iF32_vector(
        Vector__3i32F4 *vector) {
    vector->x__i32F4 =
        vector->y__i32F4 =
        vector->z__i32F4 = 0;
}

static bool inline is_3iF4_vectors__equal(
        Vector__3i32F4 vector_1,
        Vector__3i32F4 vector_2) {
    return
        vector_1.x__i32F4 == vector_2.x__i32F4
        && vector_1.y__i32F4 == vector_2.y__i32F4
        && vector_1.z__i32F4 == vector_2.z__i32F4
        ;
}

static bool inline is_3iF4_vectors__equal_without__fractional(
        Vector__3i32F4 vector_1,
        Vector__3i32F4 vector_2) {
    return
        (vector_1.x__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE) 
        == (vector_2.x__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        && (vector_1.y__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE) 
        == (vector_2.y__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        && (vector_1.z__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE) 
        == (vector_2.z__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        ;
}

#endif
