#ifndef VECTORS_H
#define VECTORS_H

/// This file includes all static inline helpers
/// to deal with vectors.

#include "defines_weak.h"
#include <defines.h>

static i32F4 inline i32_to__i32F4(Signed_Index__i32 x) {
    return x << FRACTIONAL_PERCISION_4__BIT_SIZE;
}

static Signed_Index__i32 inline i32F4_to__i32(i32F4 x) {
    return x >> FRACTIONAL_PERCISION_4__BIT_SIZE;
}

static void inline initialize_3i32F4_vector(
        Vector__3i32F4 *vector) {
    vector->x__i32F4 =
        vector->y__i32F4 =
        vector->z__i32F4 = 0;
}

static void inline initialize_3i32_vector(
        Vector__3i32 *vector) {
    vector->x__i32 =
        vector->y__i32 =
        vector->z__i32 = 0;
}

static bool inline is_vectors_3i32F4__equal(
        Vector__3i32F4 vector_1,
        Vector__3i32F4 vector_2) {
    return
        vector_1.x__i32F4 == vector_2.x__i32F4
        && vector_1.y__i32F4 == vector_2.y__i32F4
        && vector_1.z__i32F4 == vector_2.z__i32F4
        ;
}

static bool inline is_vectors_3i32F4__equal_without__fractional(
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

static bool inline is_vectors_3i32__equal(
        Vector__3i32 vector_1,
        Vector__3i32 vector_2) {
    return
        vector_1.x__i32 == vector_2.x__i32
        && vector_1.y__i32 == vector_2.y__i32
        && vector_1.z__i32 == vector_2.z__i32
        ;
}

static bool inline is_chunk_vectors_3i32__equal(
        Chunk_Vector__3i32 vector_1,
        Chunk_Vector__3i32 vector_2) {
    return is_vectors_3i32__equal(vector_1, vector_2);
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

static Vector__3i32F4 inline vector_3i32_to__vector_3i32F4(
        Vector__3i32 vector) {
    return (Vector__3i32F4){
        vector.x__i32 
            << FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.y__i32 
            << FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.z__i32 
            << FRACTIONAL_PERCISION_4__BIT_SIZE,
    };
}

static Vector__3i32F4 inline vector_3i32F8_to__vector_3i32F4(
        Vector__3i32F8 vector) {
    return (Vector__3i32F4){
        vector.x__i32F8
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.y__i32F8
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.z__i32F8
            >> FRACTIONAL_PERCISION_4__BIT_SIZE,
    };
}

static Vector__3i32F8 inline vector_3i32F4_to__vector_3i32F8(
        Vector__3i32F4 vector) {
    return (Vector__3i32F8){
        vector.x__i32F4
            << FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.y__i32F4
            << FRACTIONAL_PERCISION_4__BIT_SIZE,
        vector.z__i32F4
            << FRACTIONAL_PERCISION_4__BIT_SIZE,
    };
}

static Vector__3i32F4 inline vector_3i32F8_to__vector_3i32(
        Vector__3i32F8 vector) {
    return (Vector__3i32F4){
        vector.x__i32F8
            >> FRACTIONAL_PERCISION_8__BIT_SIZE,
        vector.y__i32F8
            >> FRACTIONAL_PERCISION_8__BIT_SIZE,
        vector.z__i32F8
            >> FRACTIONAL_PERCISION_8__BIT_SIZE,
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
        i32F4 x__fractional,
        i32F4 y,
        i32F4 y__fractional,
        i32F4 z,
        i32F4 z__fractional) {
    return (Vector__3i32F4) {
        (x << FRACTIONAL_PERCISION_4__BIT_SIZE) + x__fractional, 
        (y << FRACTIONAL_PERCISION_4__BIT_SIZE) + y__fractional, 
        (z << FRACTIONAL_PERCISION_4__BIT_SIZE) + z__fractional
    };
}

static Vector__3i32F4 inline get_vector__3i32F4_using__i32(
        i32F4 x,
        i32F4 y,
        i32F4 z) {
    return (Vector__3i32F4) {
        (x << FRACTIONAL_PERCISION_4__BIT_SIZE), 
        (y << FRACTIONAL_PERCISION_4__BIT_SIZE), 
        (z << FRACTIONAL_PERCISION_4__BIT_SIZE)
    };
}

static Signed_Index__i32 inline get_x_i32F4_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return vector__3i32F4.x__i32F4;
}

static Signed_Index__i32 inline get_y_i32F4_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return vector__3i32F4.y__i32F4;
}

static Signed_Index__i32 inline get_z_i32F4_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return vector__3i32F4.z__i32F4;
}

static Signed_Index__i32 inline get_x_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return i32F4_to__i32(
            get_x_i32F4_from__vector_3i32F4(vector__3i32F4));
}

static Signed_Index__i32 inline get_y_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return i32F4_to__i32(
            get_y_i32F4_from__vector_3i32F4(vector__3i32F4));
}

static Signed_Index__i32 inline get_z_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return i32F4_to__i32(
            get_z_i32F4_from__vector_3i32F4(vector__3i32F4));
}

static Signed_Index__i32 inline get_x_i32_from__vector_3i32(
        Vector__3i32 vector__3i32) {
    return vector__3i32.x__i32;
}

static Signed_Index__i32 inline get_y_i32_from__vector_3i32(
        Vector__3i32 vector__3i32) {
    return vector__3i32.y__i32;
}

static Signed_Index__i32 inline get_z_i32_from__vector_3i32(
        Vector__3i32 vector__3i32) {
    return vector__3i32.z__i32;
}

static Signed_Index__i32 inline *get_p_x_i32_from__p_vector_3i32(
        Vector__3i32 *p_vector__3i32) {
    return &p_vector__3i32->x__i32;
}

static Signed_Index__i32 inline *get_p_y_i32_from__p_vector_3i32(
        Vector__3i32 *p_vector__3i32) {
    return &p_vector__3i32->y__i32;
}

static Signed_Index__i32 inline *get_p_z_i32_from__p_vector_3i32(
        Vector__3i32 *p_vector__3i32) {
    return &p_vector__3i32->z__i32;
}

static Vector__3i32 inline get_vector__3i32(
        Signed_Index__i32 x,
        Signed_Index__i32 y,
        Signed_Index__i32 z) {
    return (Vector__3i32) {
        x, 
        y, 
        z
    };
}

static Vector__3i32F4 inline add_vectors__3i32F4(
        Vector__3i32F4 vector_one,
        Vector__3i32F4 vector_two) {
    return (Vector__3i32F4) {
        vector_one.x__i32F4 + vector_two.x__i32F4,
        vector_one.y__i32F4 + vector_two.y__i32F4,
        vector_one.z__i32F4 + vector_two.z__i32F4,
    };
}

static Vector__3i32 inline add_vectors__3i32(
        Vector__3i32 vector_one,
        Vector__3i32 vector_two) {
    return (Vector__3i32) {
        vector_one.x__i32 + vector_two.x__i32,
        vector_one.y__i32 + vector_two.y__i32,
        vector_one.z__i32 + vector_two.z__i32,
    };
}

static Vector__3i32F8 inline subtract_vectors__3i32F8(
        Vector__3i32F8 vector_one,
        Vector__3i32F8 vector_two) {
    return (Vector__3i32F8) {
        vector_one.x__i32F8 - vector_two.x__i32F8,
        vector_one.y__i32F8 - vector_two.y__i32F8,
        vector_one.z__i32F8 - vector_two.z__i32F8,
    };
}

static Vector__3i32F4 inline subtract_vectors__3i32F4(
        Vector__3i32F4 vector_one,
        Vector__3i32F4 vector_two) {
    return (Vector__3i32F4) {
        vector_one.x__i32F4 - vector_two.x__i32F4,
        vector_one.y__i32F4 - vector_two.y__i32F4,
        vector_one.z__i32F4 - vector_two.z__i32F4,
    };
}

static Vector__3i32 inline subtract_vectors__3i32(
        Vector__3i32 vector_one,
        Vector__3i32 vector_two) {
    return (Vector__3i32) {
        vector_one.x__i32 - vector_two.x__i32,
        vector_one.y__i32 - vector_two.y__i32,
        vector_one.z__i32 - vector_two.z__i32,
    };
}

static void inline add_p_vectors__3i32F4(
        Vector__3i32F4 *p_vector_one,
        Vector__3i32F4 *p_vector_two) {
    p_vector_one->x__i32F4 += p_vector_two->x__i32F4;
    p_vector_one->y__i32F4 += p_vector_two->y__i32F4;
    p_vector_one->z__i32F4 += p_vector_two->z__i32F4;
}

static void inline add_p_vectors__3i32F8(
        Vector__3i32F8 *p_vector_one,
        Vector__3i32F8 *p_vector_two) {
    p_vector_one->x__i32F8 += p_vector_two->x__i32F8;
    p_vector_one->y__i32F8 += p_vector_two->y__i32F8;
    p_vector_one->z__i32F8 += p_vector_two->z__i32F8;
}

static void inline add_p_vectors__3i32(
        Vector__3i32 *p_vector_one,
        Vector__3i32 *p_vector_two) {
    p_vector_one->x__i32 += p_vector_two->x__i32;
    p_vector_one->y__i32 += p_vector_two->y__i32;
    p_vector_one->z__i32 += p_vector_two->z__i32;
}

static void inline subtract_p_vectors__3i32F4(
        Vector__3i32F4 *p_vector_one,
        Vector__3i32F4 *p_vector_two) {
    p_vector_one->x__i32F4 -= p_vector_two->x__i32F4;
    p_vector_one->y__i32F4 -= p_vector_two->y__i32F4;
    p_vector_one->z__i32F4 -= p_vector_two->z__i32F4;
}

static void inline subtract_p_vectors__3i32(
        Vector__3i32 *p_vector_one,
        Vector__3i32 *p_vector_two) {
    p_vector_one->x__i32 -= p_vector_two->x__i32;
    p_vector_one->y__i32 -= p_vector_two->y__i32;
    p_vector_one->z__i32 -= p_vector_two->z__i32;
}

static bool inline is_vector_3i32F8_within__distance_i32F4(
        Vector__3i32F8 vector,
        i32F4 distance) {
    i32F4 x = vector.x__i32F8 >> FRACTIONAL_PERCISION_4__BIT_SIZE;
    i32F4 y = vector.y__i32F8 >> FRACTIONAL_PERCISION_4__BIT_SIZE;
    i32F4 z = vector.z__i32F8 >> FRACTIONAL_PERCISION_4__BIT_SIZE;
    return (x * x + y * y + z * z) <= distance * distance;
    // return ((vector.x__i32F8 * vector.x__i32F8
    //         + vector.y__i32F8 * vector.y__i32F8
    //         + vector.z__i32F8 * vector.z__i32F8)
    //         >> FRACTIONAL_PERCISION_4__BIT_SIZE)
    //     <= distance * distance
    //     ;
}

static bool inline is_vector_3i32F8_within__distance_i32(
        Vector__3i32F8 vector,
        Signed_Index__i32 distance) {
    return ((vector.x__i32F8 * vector.x__i32F8
            + vector.y__i32F8 * vector.y__i32F8
            + vector.z__i32F8 * vector.z__i32F8)
            >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        <= distance * distance
        ;
}

static bool inline is_vector_3i32F4_within__distance_i32F4(
        Vector__3i32F4 vector,
        i32F4 distance) {
    return (vector.x__i32F4 * vector.x__i32F4
            + vector.y__i32F4 * vector.y__i32F4
            + vector.z__i32F4 * vector.z__i32F4)
        <= distance * distance
        ;
}

static bool inline is_vector_3i32_within__distance_i32(
        Vector__3i32 vector,
        Signed_Index__i32 distance) {
    return (vector.x__i32 * vector.x__i32
            + vector.y__i32 * vector.y__i32
            + vector.z__i32 * vector.z__i32)
        <= distance * distance
        ;
}

#endif
