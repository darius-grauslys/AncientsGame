#ifndef VECTORS_H
#define VECTORS_H

/// This file includes all static inline helpers
/// to deal with vectors.

#include "defines_weak.h"
#include <defines.h>
#include <numerics.h>

#define VECTOR__0_0_0 {\
        0,\
        0,\
        0}

#define VECTOR__OUT_OF_BOUNDS {\
        BIT(31),\
        BIT(31),\
        BIT(31)}

#define VECTOR__3i32__0_0_0 \
    (const Vector__3i32) VECTOR__0_0_0
#define VECTOR__3i32F4__0_0_0 \
    (const Vector__3i32F4) VECTOR__0_0_0
#define VECTOR__3i32F4__1_0_0 \
        (const Vector__3i32F4){\
        i32_to__i32F4(1),\
        0,\
        0}
#define VECTOR__3i32F4__n1_0_0 \
        (const Vector__3i32F4){\
        -i32_to__i32F4(1),\
        0,\
        0}
#define VECTOR__3i32F4__0_1_0 \
        (const Vector__3i32F4){\
        0,\
        i32_to__i32F4(1),\
        0}
#define VECTOR__3i32F4__0_n1_0 \
        (const Vector__3i32F4){\
        0,\
        -i32_to__i32F4(1),\
        0}
#define VECTOR__3i32F20__0_0_0 \
    (const Vector__3i32F20) VECTOR__0_0_0

#define VECTOR__3i32__OUT_OF_BOUNDS \
    (const Vector__3i32) VECTOR__OUT_OF_BOUNDS
#define VECTOR__3i32F4__OUT_OF_BOUNDS \
    (const Vector__3i32F4) VECTOR__OUT_OF_BOUNDS
#define VECTOR__3i32F20__OUT_OF_BOUNDS \
    (const Vector__3i32F20) VECTOR__OUT_OF_BOUNDS

static inline
bool is_vectors_3i32__out_of_bounds(
        const Vector__3i32 vector__3i32) {
    return 
        VECTOR__3i32__OUT_OF_BOUNDS.x__i32
        == vector__3i32.x__i32
        || VECTOR__3i32__OUT_OF_BOUNDS.y__i32
        == vector__3i32.y__i32
        || VECTOR__3i32__OUT_OF_BOUNDS.z__i32
        == vector__3i32.z__i32
        ;
}

static inline
bool is_vectors_3i32F4__out_of_bounds(
        const Vector__3i32F4 vector__3i32F4) {
    return 
        VECTOR__3i32F4__OUT_OF_BOUNDS.x__i32F4
        == vector__3i32F4.x__i32F4
        || VECTOR__3i32F4__OUT_OF_BOUNDS.y__i32F4
        == vector__3i32F4.y__i32F4
        || VECTOR__3i32F4__OUT_OF_BOUNDS.z__i32F4
        == vector__3i32F4.z__i32F4
        ;
}

static inline
bool is_vectors_3i32F20__out_of_bounds(
        const Vector__3i32F20 vector__3i32F20) {
    return 
        VECTOR__3i32F20__OUT_OF_BOUNDS.x__i32F20
        == vector__3i32F20.x__i32F20
        || VECTOR__3i32F20__OUT_OF_BOUNDS.y__i32F20
        == vector__3i32F20.y__i32F20
        || VECTOR__3i32F20__OUT_OF_BOUNDS.z__i32F20
        == vector__3i32F20.z__i32F20
        ;
}

static inline 
void initialize_3i32F4_vector(
        Vector__3i32F4 *vector) {
    vector->x__i32F4 =
        vector->y__i32F4 =
        vector->z__i32F4 = 0;
}

static inline 
void initialize_3i32_vector(
        Vector__3i32 *vector) {
    vector->x__i32 =
        vector->y__i32 =
        vector->z__i32 = 0;
}

static inline 
bool is_vectors_3i32F4__equal(
        Vector__3i32F4 vector_1,
        Vector__3i32F4 vector_2) {
    return
        vector_1.x__i32F4 == vector_2.x__i32F4
        && vector_1.y__i32F4 == vector_2.y__i32F4
        && vector_1.z__i32F4 == vector_2.z__i32F4
        ;
}

static inline 
bool is_vectors_3i32F20__equal(
        Vector__3i32F20 vector_1,
        Vector__3i32F20 vector_2) {
    return
        vector_1.x__i32F20 == vector_2.x__i32F20
        && vector_1.y__i32F20 == vector_2.y__i32F20
        && vector_1.z__i32F20 == vector_2.z__i32F20
        ;
}

// static bool inline is_vectors_3i32F4__equal_without__fractional(
//         Vector__3i32F4 vector_1,
//         Vector__3i32F4 vector_2) {
//     return
//         (vector_1.x__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE) 
//         == (vector_2.x__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
//         && (vector_1.y__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE) 
//         == (vector_2.y__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
//         && (vector_1.z__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE) 
//         == (vector_2.z__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
//         ;
// }

static inline 
bool is_vectors_3i32__equal(
        Vector__3i32 vector_1,
        Vector__3i32 vector_2) {
    return
        vector_1.x__i32 == vector_2.x__i32
        && vector_1.y__i32 == vector_2.y__i32
        && vector_1.z__i32 == vector_2.z__i32
        ;
}

static inline 
bool is_chunk_vectors_3i32__equal(
        Chunk_Vector__3i32 vector_1,
        Chunk_Vector__3i32 vector_2) {
    return is_vectors_3i32__equal(vector_1, vector_2);
}

void offset_vector_by__direction(
        Vector__3i32F4 *vector,
        Direction__u8 direction);

static inline 
Vector__3i32 vector_3i32F4_to__vector_3i32(
        Vector__3i32F4 vector) {
    return (Vector__3i32){
        i32F4_to__i32(vector.x__i32F4),
        i32F4_to__i32(vector.y__i32F4),
        i32F4_to__i32(vector.z__i32F4)
    };
}

static inline 
Vector__3i32F4 vector_3i32_to__vector_3i32F4(
        Vector__3i32 vector) {
    return (Vector__3i32F4){
        i32_to__i32F4(vector.x__i32),
        i32_to__i32F4(vector.y__i32),
        i32_to__i32F4(vector.z__i32)
    };
}

static inline 
Vector__3i32F4 vector_3i32F20_to__vector_3i32F4(
        Vector__3i32F20 vector) {
    return (Vector__3i32F4){
        i32F20_to__i32F4(vector.x__i32F20),
        i32F20_to__i32F4(vector.y__i32F20),
        i32F20_to__i32F4(vector.z__i32F20)
    };
}

static inline 
Vector__3i32F20 vector_3i32F4_to__vector_3i32F20(
        Vector__3i32F4 vector) {
    return (Vector__3i32F20){
        i32F4_to__i32F20(vector.x__i32F4),
        i32F4_to__i32F20(vector.y__i32F4),
        i32F4_to__i32F20(vector.z__i32F4)
    };
}

static inline 
Vector__3i32 vector_3i32F20_to__vector_3i32(
        Vector__3i32F20 vector) {
    return (Vector__3i32){
        i32F20_to__i32(vector.x__i32F20),
        i32F20_to__i32(vector.y__i32F20),
        i32F20_to__i32(vector.z__i32F20)
    };
}

static inline 
Vector__3u8 vector_3i32F4_to__vector_3u8(
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

static inline 
Vector__3u8 get_vector__3u8(
        u8 x,
        u8 y,
        u8 z) {
    return (Vector__3u8) {
        x, 
        y, 
        z
    };
}

static inline 
Vector__3i32F4 get_vector__3i32F4(
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

static inline 
Vector__3i32F4 get_vector__3i32F4_using__i32(
        i32F4 x,
        i32F4 y,
        i32F4 z) {
    return (Vector__3i32F4) {
        (x << FRACTIONAL_PERCISION_4__BIT_SIZE), 
        (y << FRACTIONAL_PERCISION_4__BIT_SIZE), 
        (z << FRACTIONAL_PERCISION_4__BIT_SIZE)
    };
}

static inline 
Signed_Index__i32 get_x_i32F4_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return vector__3i32F4.x__i32F4;
}

static inline 
Signed_Index__i32 get_y_i32F4_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return vector__3i32F4.y__i32F4;
}

static inline 
Signed_Index__i32 get_z_i32F4_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return vector__3i32F4.z__i32F4;
}

static inline 
Signed_Index__i32 get_x_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return i32F4_to__i32(
            get_x_i32F4_from__vector_3i32F4(vector__3i32F4));
}

static inline 
Signed_Index__i32 get_y_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return i32F4_to__i32(
            get_y_i32F4_from__vector_3i32F4(vector__3i32F4));
}

static inline 
Signed_Index__i32 get_z_i32_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return i32F4_to__i32(
            get_z_i32F4_from__vector_3i32F4(vector__3i32F4));
}

static inline 
Signed_Index__i32 get_x_i32_from__vector_3i32(
        Vector__3i32 vector__3i32) {
    return vector__3i32.x__i32;
}

static inline 
Signed_Index__i32 get_y_i32_from__vector_3i32(
        Vector__3i32 vector__3i32) {
    return vector__3i32.y__i32;
}

static inline 
Signed_Index__i32 get_z_i32_from__vector_3i32(
        Vector__3i32 vector__3i32) {
    return vector__3i32.z__i32;
}

static inline 
Signed_Index__i32 *get_p_x_i32_from__p_vector_3i32(
        Vector__3i32 *p_vector__3i32) {
    return &p_vector__3i32->x__i32;
}

static inline 
Signed_Index__i32 *get_p_y_i32_from__p_vector_3i32(
        Vector__3i32 *p_vector__3i32) {
    return &p_vector__3i32->y__i32;
}

static inline 
Signed_Index__i32 *get_p_z_i32_from__p_vector_3i32(
        Vector__3i32 *p_vector__3i32) {
    return &p_vector__3i32->z__i32;
}

static inline 
Vector__3i32 get_vector__3i32(
        Signed_Index__i32 x,
        Signed_Index__i32 y,
        Signed_Index__i32 z) {
    return (Vector__3i32) {
        x, 
        y, 
        z
    };
}

static inline 
Vector__3i32F4 add_vectors__3i32F4(
        Vector__3i32F4 vector_one,
        Vector__3i32F4 vector_two) {
    return (Vector__3i32F4) {
        vector_one.x__i32F4 + vector_two.x__i32F4,
        vector_one.y__i32F4 + vector_two.y__i32F4,
        vector_one.z__i32F4 + vector_two.z__i32F4,
    };
}

static inline 
Vector__3i32 add_vectors__3i32(
        Vector__3i32 vector_one,
        Vector__3i32 vector_two) {
    return (Vector__3i32) {
        vector_one.x__i32 + vector_two.x__i32,
        vector_one.y__i32 + vector_two.y__i32,
        vector_one.z__i32 + vector_two.z__i32,
    };
}

static inline 
Vector__3i32F20 subtract_vectors__3i32F20(
        Vector__3i32F20 vector_one,
        Vector__3i32F20 vector_two) {
    return (Vector__3i32F20) {
        vector_one.x__i32F20 - vector_two.x__i32F20,
        vector_one.y__i32F20 - vector_two.y__i32F20,
        vector_one.z__i32F20 - vector_two.z__i32F20,
    };
}

static inline 
Vector__3i32F4 subtract_vectors__3i32F4(
        Vector__3i32F4 vector_one,
        Vector__3i32F4 vector_two) {
    return (Vector__3i32F4) {
        vector_one.x__i32F4 - vector_two.x__i32F4,
        vector_one.y__i32F4 - vector_two.y__i32F4,
        vector_one.z__i32F4 - vector_two.z__i32F4,
    };
}

static inline 
Vector__3i32 subtract_vectors__3i32(
        Vector__3i32 vector_one,
        Vector__3i32 vector_two) {
    return (Vector__3i32) {
        vector_one.x__i32 - vector_two.x__i32,
        vector_one.y__i32 - vector_two.y__i32,
        vector_one.z__i32 - vector_two.z__i32,
    };
}

static inline 
void add_p_vectors__3i32F4(
        Vector__3i32F4 *p_vector_one,
        Vector__3i32F4 *p_vector_two) {
    p_vector_one->x__i32F4 += p_vector_two->x__i32F4;
    p_vector_one->y__i32F4 += p_vector_two->y__i32F4;
    p_vector_one->z__i32F4 += p_vector_two->z__i32F4;
}

static inline 
void add_p_vectors__3i32F20(
        Vector__3i32F20 *p_vector_one,
        Vector__3i32F20 *p_vector_two) {
    p_vector_one->x__i32F20 += p_vector_two->x__i32F20;
    p_vector_one->y__i32F20 += p_vector_two->y__i32F20;
    p_vector_one->z__i32F20 += p_vector_two->z__i32F20;
}

static inline 
void add_p_vectors__3i32(
        Vector__3i32 *p_vector_one,
        Vector__3i32 *p_vector_two) {
    p_vector_one->x__i32 += p_vector_two->x__i32;
    p_vector_one->y__i32 += p_vector_two->y__i32;
    p_vector_one->z__i32 += p_vector_two->z__i32;
}

static inline 
void subtract_p_vectors__3i32F4(
        Vector__3i32F4 *p_vector_one,
        Vector__3i32F4 *p_vector_two) {
    p_vector_one->x__i32F4 -= p_vector_two->x__i32F4;
    p_vector_one->y__i32F4 -= p_vector_two->y__i32F4;
    p_vector_one->z__i32F4 -= p_vector_two->z__i32F4;
}

static inline 
void subtract_p_vectors__3i32(
        Vector__3i32 *p_vector_one,
        Vector__3i32 *p_vector_two) {
    p_vector_one->x__i32 -= p_vector_two->x__i32;
    p_vector_one->y__i32 -= p_vector_two->y__i32;
    p_vector_one->z__i32 -= p_vector_two->z__i32;
}

static inline
i32 get_distance_squared_of__vector_3i32(
        Vector__3i32 vector__3i32) {
    return (vector__3i32.x__i32 * vector__3i32.x__i32
            + vector__3i32.y__i32 * vector__3i32.y__i32
            + vector__3i32.z__i32 * vector__3i32.z__i32)
        ;
}

static inline
i32F4 get_distance_squared_of__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return (vector__3i32F4.x__i32F4 * vector__3i32F4.x__i32F4
            + vector__3i32F4.y__i32F4 * vector__3i32F4.y__i32F4
            + vector__3i32F4.z__i32F4 * vector__3i32F4.z__i32F4)
        >> FRACTIONAL_PERCISION_4__BIT_SIZE
        ;
}

// TODO: can we perserve more percision?
static inline
i32F20 get_distance_squared_of__vector_3i32F20(
        Vector__3i32F20 vector__3i32F20) {
    Vector__3i32F4 vector__3i32F4 =
        vector_3i32F20_to__vector_3i32F4(vector__3i32F20);
    return
        get_distance_squared_of__vector_3i32F4(vector__3i32F4);
}

static inline
i32F4 get_distance_hamming_of__vectors_3i32(
        Vector__3i32 vector__one__3i32,
        Vector__3i32 vector__two__3i32) {
    return
        abs(vector__one__3i32.x__i32
                - vector__two__3i32.x__i32)
        + abs(vector__one__3i32.y__i32
                - vector__two__3i32.y__i32)
        + abs(vector__one__3i32.z__i32
                - vector__two__3i32.z__i32)
        ;
}

static inline
i32F4 get_distance_hamming_of__vectors_3i32F4(
        Vector__3i32F4 vector__one__3i32F4,
        Vector__3i32F4 vector__two__3i32F4) {
    return
        abs(vector__one__3i32F4.x__i32F4
                - vector__two__3i32F4.x__i32F4)
        + abs(vector__one__3i32F4.y__i32F4
                - vector__two__3i32F4.y__i32F4)
        + abs(vector__one__3i32F4.z__i32F4
                - vector__two__3i32F4.z__i32F4)
        ;
}

static inline 
bool is_vector_3i32F20_within__squared_distance_i32(
        Vector__3i32F20 vector,
        i32 distance) {
    i32 x = i32F20_to__i32(vector.x__i32F20);
    i32 y = i32F20_to__i32(vector.y__i32F20);
    i32 z = i32F20_to__i32(vector.z__i32F20);
    return (x * x + y * y + z * z) <= distance;
    // return ((vector.x__i32F20 * vector.x__i32F20
    //         + vector.y__i32F20 * vector.y__i32F20
    //         + vector.z__i32F20 * vector.z__i32F20)
    //         >> FRACTIONAL_PERCISION_4__BIT_SIZE)
    //     <= distance * distance
    //     ;
}

static inline 
bool is_vector_3i32F4_within__distance_i32F4(
        Vector__3i32F4 vector,
        i32F4 distance) {
    return (vector.x__i32F4 * vector.x__i32F4
            + vector.y__i32F4 * vector.y__i32F4
            + vector.z__i32F4 * vector.z__i32F4)
        <= distance * distance
        ;
}

static inline 
bool is_vector_3i32_within__distance_i32(
        Vector__3i32 vector,
        Signed_Index__i32 distance) {
    return (vector.x__i32 * vector.x__i32
            + vector.y__i32 * vector.y__i32
            + vector.z__i32 * vector.z__i32)
        <= distance * distance
        ;
}

#endif
