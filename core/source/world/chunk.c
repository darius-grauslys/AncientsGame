#include <world/chunk.h>

void init_chunk(Chunk *chunk, int32_t x, int32_t y) {
    chunk->x = x;
    chunk->y = y;
}

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
void set_tile_of__chunk(Chunk* chunk, 
        int32_t x, int32_t y, int32_t z, 
        Tile* tile) {
    //TODO: we need debug stuffs.
    int32_t index =
        (z * CHUNK__WIDTH * CHUNK__HEIGHT)
        + (y * CHUNK__WIDTH)
        + x
        ;

    chunk->tiles[index] = *tile;
}

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
Tile* get_tile_from__chunk(Chunk *chunk, int32_t x, int32_t y, int32_t z) {
    int32_t index = (1 << (z * CHUNK__DEPTH_BIT_SHIFT)) +
        (1 << (y * CHUNK__HEIGHT_BIT_SHIFT)) + x;

    return &chunk->tiles[index];
}
