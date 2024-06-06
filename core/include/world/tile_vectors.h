#ifndef TILE_VECTORS_H
#define TILE_VECTORS_H

#include "defines_weak.h"
#include "world/chunk_vectors.h"
#include <defines.h>
#include <vectors.h>

static Index__u8 inline normalize_i32__to_tile_u8(
        Signed_Index__i32 x) {
    return 
        (x >> 3) & ((1 << 3) - 1);
}

static Index__u8 inline get_tile_x_u8_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return 
        normalize_i32__to_tile_u8(
                get_x_i32_from__vector_3i32F4(vector__3i32F4));
}

static Index__u8 inline get_tile_y_u8_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return 
        normalize_i32__to_tile_u8(
                get_y_i32_from__vector_3i32F4(vector__3i32F4));
}

static Index__u8 inline get_tile_z_u8_from__vector_3i32F4(
        Vector__3i32F4 vector__3i32F4) {
    return 
        normalize_i32__to_tile_u8(
                get_z_i32_from__vector_3i32F4(vector__3i32F4));
}

static Tile_Vector__3i32 inline get_tile_vector__3i32(
        Signed_Index__i32 x,
        Signed_Index__i32 y,
        Signed_Index__i32 z) {
    return (Vector__3i32) {
        x >> ENTITY_TILE_LOCAL_SPACE__BIT_SIZE, 
        y >> ENTITY_TILE_LOCAL_SPACE__BIT_SIZE, 
        z >> ENTITY_TILE_LOCAL_SPACE__BIT_SIZE
    };
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

///
/// Returns a Vector__3u8 with x,y,z signlessly indexing tiles
///
static inline Local_Tile_Vector__3u8 vector_3i32F4_to__local_tile_vector_3u8(
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
