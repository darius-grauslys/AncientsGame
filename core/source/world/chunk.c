#include <world/chunk.h>

void init_chunk(Chunk *chunk, int32_t x, int32_t y) {
    for (int i=0;i<CHUNK__QUANTITY_OF_TILES;i++) {
        init_tile(&chunk->tiles[i], Tile_Kind__Void, TILE_FLAGS__NONE);
    }
    chunk->x = x;
    chunk->y = y;
}

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
void set_tile_of_chunk(Chunk* chunk, 
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
Tile* get_tile_from_chunk(Chunk *chunk, int32_t x, int32_t y, int32_t z) {
    int32_t index = (1 << (z * CHUNK__DEPTH_BIT_SHIFT)) +
        (1 << (y * CHUNK__HEIGHT_BIT_SHIFT)) + x;

    return &chunk->tiles[index];
}
