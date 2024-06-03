#ifndef VECTORS_H
#define VECTORS_H

/// This file includes all static inline helpers
/// to deal with vectors.

#include <defines.h>

static void inline initialize_3iF32_vector(
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

void offset_vector_by__direction(
        Vector__3i32F4 *vector,
        Direction__u8 direction);

static Vector__3i32 inline vector_3i32F4_to__vector_3i32(
        Vector__3i32F4 vector) {
    return (Vector__3i32){
        vector.x__i32F4 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.y__i32F4 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.z__i32F4 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
    };
}

static Vector__3u8 inline vector_3i32F4_to__vector_3u8(
        Vector__3i32F4 vector) {
    return (Vector__3u8){
        vector.x__i32F4 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.y__i32F4 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.z__i32F4 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
    };
}

static Vector__3i32F4 inline get_vector__3i32F4(
        i32F4 x,
        i32F4 y,
        i32F4 z) {
    return (Vector__3i32F4) {
        x, y, z
    };
}

#endif
