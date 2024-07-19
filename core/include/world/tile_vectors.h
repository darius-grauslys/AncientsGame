#ifndef TILE_VECTORS_H
#define TILE_VECTORS_H

#include "defines_weak.h"
#include "world/chunk_vectors.h"
#include <defines.h>
#include <vectors.h>

static inline
i32 normalize_xyz_i32F4_to__tile_xyz_i32(i32F4 xyz__i32F4) {
    //TODO: magic number
    return (xyz__i32F4
        >> 7)
        - (xyz__i32F4 < 0 
                && xyz__i32F4 > i32_to__i32F4(-8));
}

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

static inline 
Tile_Vector__3i32 get_tile_vector(
        Signed_Index__i32 x,
        Signed_Index__i32 y,
        Signed_Index__i32 z) {
    //TODO: magic number
    return (Vector__3i32) {
        x >> 3, 
        y >> 3, 
        z >> 3
    };
}

static Tile_Vector__3i32 inline get_tile_vector_using__i32F4(
        i32F4 x,
        i32F4 y,
        i32F4 z) {
    // TODO: magic number
    return (Vector__3i32) {
        i32F4_to__i32(x) >> 3, 
        i32F4_to__i32(y) >> 3, 
        i32F4_to__i32(z) >> 3
    };
}

static Tile_Vector__3i32 inline vector_3i32F4_to__tile_vector(
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

static Tile_Vector__3i32 inline vector_3i32F20_to__tile_vector(
        Vector__3i32F20 vector) {
    return (Tile_Vector__3i32) {
        vector.x__i32F20 >> 11,
        vector.y__i32F20 >> 11,
        vector.z__i32F20 >> 11,
    };
}

static inline
Tile_Vector__3i32 get_ray_endpoint_as__tile_vector(
        Ray__3i32F20 *p_ray) {
    return vector_3i32F20_to__tile_vector(
            p_ray->ray_current_vector__3i32F20);
}

///
/// Returns a Vector__3u8 with x,y,z signlessly indexing tiles
///
static inline Local_Tile_Vector__3u8 vector_3i32F4_to__local_tile_vector_3u8(
        Vector__3i32F4 vector) {
    Vector__3i32 vector__3i32 =
        vector_3i32F4_to__vector_3i32(vector);
    vector__3i32.x__i32 = (((vector__3i32.x__i32 >> 3)
            % CHUNK_WIDTH__IN_TILES) + CHUNK_WIDTH__IN_TILES)
        % CHUNK_WIDTH__IN_TILES;
    vector__3i32.y__i32 = (((vector__3i32.y__i32 >> 3)
            % CHUNK_WIDTH__IN_TILES) + CHUNK_WIDTH__IN_TILES)
        % CHUNK_WIDTH__IN_TILES;
    vector__3i32.z__i32 = (((vector__3i32.z__i32 >> 3)
            % CHUNK_WIDTH__IN_TILES) + CHUNK_WIDTH__IN_TILES)
        % CHUNK_WIDTH__IN_TILES;
    return get_vector__3u8(
            vector__3i32.x__i32, 
            vector__3i32.y__i32, 
            vector__3i32.z__i32);
}

#endif
