#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <defines.h>

void init_chunk_manager(Chunk_Manager* manager);

Chunk* get_chunk_from_chunk_manager(Chunk_Manager* manager, 
        int world_x, int world_y, int world_z);

///
/// The chunk manager will set the given chunk as the center
/// of the managed space. Resulting in some chunks getting
/// marked for release, and likely getting overwritten for
/// new loaded chunks.
///
void set_chunk_as_center_for_chunk_manager(
        Chunk_Manager* manager, Chunk* chunk);
Chunk* get_neighboring_chunk(Chunk_Manager* manager,
        Chunk* chunk, enum Direction direction);

void release_chunk_manager(Chunk_Manager* manager);

#endif
