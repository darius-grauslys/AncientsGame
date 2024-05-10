#ifndef CHUNK_H
#define CHUNK_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

#include "tile.h"

static inline void init_chunk(Chunk *chunk, int32_t x, int32_t y) {
    chunk->x = x;
    chunk->y = y;
}

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
static inline void set_tile_of__chunk(Chunk* chunk, 
        int32_t x, int32_t y, int32_t z, 
        Tile* tile) {
    //TODO: we need debug stuffs.
    int32_t index = (1 << (z * CHUNK__DEPTH_BIT_SHIFT)) +
        (1 << (y * CHUNK__HEIGHT_BIT_SHIFT)) + x;

    chunk->tiles[index] = *tile;
}

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
static inline Tile* get_tile_from__chunk(Chunk *chunk, int32_t x, int32_t y, int32_t z) {
    // int32_t index = (1 << (z * CHUNK__DEPTH_BIT_SHIFT)) +
    //     ((CHUNK_WIDTH__IN_TILES - y) << CHUNK__HEIGHT_BIT_SHIFT) + x;
    int32_t index = x + (7-y) * 8;

    return &chunk->tiles[index];
}

#endif
