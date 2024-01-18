#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <defines.h>

void init_chunk_manager(
        Chunk_Manager* chunk_manager,
        World_Parameters *world_params);

uint32_t get_chunk_index_from__chunk_xy(
        Chunk_Manager *chunk_manager,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk);

Chunk* get_chunk_from__chunk_manager(
        Chunk_Manager* chunk_manager, 
        int32_t x__chunk, int32_t y__chunk, 
        int32_t z__chunk);

void move_chunk_manager__chunks(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        Direction direction,
        uint32_t steps);

bool poll_chunk_manager__for_chunk_movement(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk);

#endif
