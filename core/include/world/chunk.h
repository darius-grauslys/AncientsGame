#ifndef CHUNK_H
#define CHUNK_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

#include "tile.h"

#define CHUNK__WIDTH_BIT_SHIFT 3
#define CHUNK__HEIGHT_BIT_SHIFT 3
#define CHUNK__DEPTH_BIT_SHIFT (CHUNK__WIDTH_BIT_SHIFT + CHUNK__HEIGHT_BIT_SHIFT)

#define CHUNK__WIDTH (1 << CHUNK__WIDTH_BIT_SHIFT)
#define CHUNK__HEIGHT (1 << CHUNK__HEIGHT_BIT_SHIFT)
// depth is 1 until AFTER the adventure update.
#define CHUNK__DEPTH (1)

#define CHUNK__QUANTITY_OF_TILES (CHUNK__WIDTH * \
        CHUNK__HEIGHT * CHUNK__DEPTH)

typedef struct Chunk_t {
    Tile tiles[CHUNK__WIDTH * CHUNK__HEIGHT * CHUNK__DEPTH];
    int32_t x, y;
    bool is_available;
} Chunk;

void init_chunk(Chunk *chunk, int32_t x, int32_t y);

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
void set_tile_of_chunk(Chunk* chunk, 
        int32_t x, int32_t y, int32_t z, 
        Tile* tile);

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
Tile* get_tile_from_chunk(Chunk *chunk, 
        int32_t x, int32_t y, int32_t z);

#endif
