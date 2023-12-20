#ifndef CHUNK_H
#define CHUNK_H

#include <defines.h>

unsigned char get_width_or_length_of_chunk(void);
unsigned char get_height_of_chunk(void);
unsigned int get_number_of_tiles_in_a_chunk(void);
unsigned int get_number_of_tiles_in_a_chunk_layer(void);

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
void set_tile_of_chunk(Chunk* chunk, int x, int y, int z, Tile* tile);

///
/// x, y, and z are local to the chunk.
/// Implementation should store tiles sequentially in memory.
/// So, x=0, y=0, z=0 gets us the first tile in memory.
///
Tile* get_tile_from_chunk(Chunk *chunk, int x, int y, int z);

#endif
