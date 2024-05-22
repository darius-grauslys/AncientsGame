#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <defines.h>

void init_chunk_manager(
        Chunk_Manager* chunk_manager,
        World_Parameters *world_params);

uint32_t get_chunk_index_at__xyz_from__chunk_manager(
        Chunk_Manager *chunk_manager,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk);

Chunk* get_chunk_from__chunk_manager(
        Chunk_Manager* chunk_manager, 
        int32_t x__chunk, int32_t y__chunk, 
        int32_t z__chunk);

void move_chunk_manager(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        Direction direction,
        uint32_t steps);

bool poll_chunk_manager_for__chunk_movement(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk);

bool poll_chunk_manager_for__tile_collision(
        Chunk_Manager *chunk_manager,
        Entity *entity);

static Tile inline *get_tile_from__chunk_node(
        Chunk_Manager__Chunk_Map_Node *chunk_node,
        int32_t x__local, int32_t y__local) {
#ifndef NDEBUG
    if (x__local < 0 
            || x__local >= CHUNK_WIDTH__IN_TILES
            || y__local < 0
            || y__local >= CHUNK_WIDTH__IN_TILES) {
        debug_error("get_tile_from__chunk_node out of bounds %d,%d", 
                x__local, y__local);
        return &chunk_node->chunk__here->tiles[0];
    }
#endif
    return &chunk_node->chunk__here->tiles[
        y__local * CHUNK_WIDTH__IN_TILES + x__local];
}

#endif
