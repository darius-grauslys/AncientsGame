#ifndef VECTORS_H
#define VECTORS_H

/// This file includes all static inline helpers
/// to deal with vectors.

#include <defines.h>

static void inline initialize_3i32F4_vector(
        Vector__3i32F4 *vector) {
    vector->x__i32F4 =
        vector->y__i32F4 =
        vector->z__i32F4 = 0;
}

static bool inline is_3i32F4_vectors__equal(
        Vector__3i32F4 vector_1,
        Vector__3i32F4 vector_2) {
    return
        vector_1.x__i32F4 == vector_2.x__i32F4
        && vector_1.y__i32F4 == vector_2.y__i32F4
        && vector_1.z__i32F4 == vector_2.z__i32F4
        ;
}

static bool inline is_3i32F4_vectors__equal_without__fractional(
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

static Vector__3i32F4 inline get_vector__3i32F4_with__3i32(
        i32F4 x,
        i32F4 y,
        i32F4 z) {
    return (Vector__3i32F4) {
        (x << FRACTIONAL_PERCISION_4__BIT_SIZE), 
        (y << FRACTIONAL_PERCISION_4__BIT_SIZE), 
        (z << FRACTIONAL_PERCISION_4__BIT_SIZE)
    };
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

static Tile_Vector__3i32 inline vector_3i32F4_to__tile_vector_3i32(
        Vector__3i32F4 vector) {
    return (Tile_Vector__3i32) {
        vector.x__i32F4 
            >> ENTITY_TILE_FRACTIONAL__BIT_SIZE,
        vector.y__i32F4 
            >> ENTITY_TILE_FRACTIONAL__BIT_SIZE,
        vector.z__i32F4 
            >> ENTITY_TILE_FRACTIONAL__BIT_SIZE,
    };
}

static Chunk_Vector__3i32 inline vector_3i32F4_to__chunk_vector_3i32(
        Vector__3i32F4 vector) {
    return (Tile_Vector__3i32) {
        vector.x__i32F4 
            >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE,
        vector.y__i32F4 
            >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE,
        vector.z__i32F4
            >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE
    };
}

static Chunk_Vector__3i32 inline vector_3i32_to__chunk_vector_3i32(
        Vector__3i32 vector) {
    return (Tile_Vector__3i32) {
        vector.x__i32 
            >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE,
        vector.y__i32 
            >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE,
        vector.z__i32
            >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE
    };
}

///
/// Returns a Vector__3u8 with x,y,z signlessly indexing tiles
///
static inline Vector__3u8 vector_3i32F4_to__local_chunk_vector_3u8(
        Vector__3i32F4 vector) {
    Vector__3i32 vector__3i32 =
        vector_3i32F4_to__vector_3i32(vector);
    vector__3i32.x__i32 = ((vector__3i32.x__i32 
            % CHUNK_WIDTH__IN_TILES) + CHUNK_WIDTH__IN_TILES)
        % CHUNK_WIDTH__IN_TILES;
    vector__3i32.y__i32 = ((vector__3i32.y__i32 
            % CHUNK_WIDTH__IN_TILES) + CHUNK_WIDTH__IN_TILES)
        % CHUNK_WIDTH__IN_TILES;
    vector__3i32.z__i32 = ((vector__3i32.z__i32 
            % CHUNK_WIDTH__IN_TILES) + CHUNK_WIDTH__IN_TILES)
        % CHUNK_WIDTH__IN_TILES;
    Vector__3u8 vector__3u8 =
        vector_3i32F4_to__vector_3u8(vector);
    return vector__3u8;
}

#endif
