#ifndef CHUNK_H
#define CHUNK_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

#include "platform_defines.h"
#include "tile.h"
#include "vectors.h"

static inline void initialize_chunk(
        Chunk *chunk, 
        Signed_Index__i32 x__signed_index_i32, 
        Signed_Index__i32 y__signed_index_i32) {
    chunk->x__signed_index_i32 = x__signed_index_i32;
    chunk->y__signed_index_i32 = y__signed_index_i32;
}

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
static inline void set_tile_of__chunk(
        Chunk* chunk, 
        Signed_Index__i32 x__signed_index_i32, 
        Signed_Index__i32 y__signed_index_i32, 
        Signed_Index__i32 z__signed_index_i32, 
        Tile* tile) {
    //TODO: we need debug stuffs.
    int32_t index = (1 << (z__signed_index_i32 * CHUNK__DEPTH_BIT_SHIFT))
        + (1 << (y__signed_index_i32 * CHUNK__HEIGHT_BIT_SHIFT)) 
        + x__signed_index_i32;

    chunk->tiles[index] = *tile;
}

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
static inline Tile* get_tile_ptr_from__chunk(
        Chunk *chunk, 
        Chunk_Tile_Index__u8 x__chunk_tile_index_u8, 
        Chunk_Tile_Index__u8 y__chunk_tile_index_u8, 
        Chunk_Tile_Index__u8 z__chunk_tile_index_u8) {
    // int32_t index = (1 << (z * CHUNK__DEPTH_BIT_SHIFT)) +
    //     ((CHUNK_WIDTH__IN_TILES - y) << CHUNK__HEIGHT_BIT_SHIFT) + x;
    Index__u8 index__u8 = 
        x__chunk_tile_index_u8 
        + (7 - y__chunk_tile_index_u8) 
        * 8;

    return &chunk->tiles[index__u8];
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

///
/// Returns a Vector__3i32 with x,y,z indexing chunks.
///
static inline Vector__3i32 vector_3i32F4_to__chunk_vector_3i32(
        Vector__3i32F4 vector) {
    Vector__3i32 vector__3i32 =
        vector_3i32F4_to__vector_3i32(vector);
    vector__3i32.x__i32 >>= CHUNK__WIDTH_BIT_SHIFT;
    vector__3i32.y__i32 >>= CHUNK__WIDTH_BIT_SHIFT;
    vector__3i32.z__i32 >>= CHUNK__WIDTH_BIT_SHIFT;
    return vector__3i32;
}

#endif
