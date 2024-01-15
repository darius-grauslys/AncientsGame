#ifndef CHUNK_H
#define CHUNK_H

#include <stdbool.h>
#include <stdint.h>
#include <defines.h>

#include "tile.h"

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
