#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <defines.h>

void init_chunk_manager(
        Chunk_Manager* manager,
        World_Parameters *world_params);

Chunk* get_chunk_from__chunk_manager(
        Chunk_Manager* manager, 
        int32_t global_chunk_x, int32_t global_chunk_y, 
        int32_t global_chunk_z);

void move_chunk_manager__chunks(
        Chunk_Manager *manager,
        World_Parameters *world_params,
        Direction direction,
        uint32_t steps);

bool poll_chunk_manager__for_chunk_movement(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        int32_t x__chunk, int32_t y__chunk);

#endif
