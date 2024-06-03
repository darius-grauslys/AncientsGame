#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_chunk_manager(
        Chunk_Manager* p_chunk_manager,
        World_Parameters *p_world_parameters);

Index_u32 get_chunk_index_at__xyz_from__chunk_manager(
        Chunk_Manager *p_chunk_manager,
        Signed_Index__i32 x__chunk, 
        Signed_Index__i32 y__chunk,
        Signed_Index__i32 z__chunk);

Chunk* get_chunk_ptr_from__chunk_manager(
        Chunk_Manager *p_chunk_manager, 
        Signed_Index__i32 x__chunk, 
        Signed_Index__i32 y__chunk, 
        Signed_Index__i32 z__chunk);

void move_chunk_manager(
        Chunk_Manager *p_chunk_manager,
        World_Parameters *p_world_parameters,
        Direction__u8 direction,
        Quantity__u32 steps);

bool poll_chunk_manager_for__chunk_movement(
        Chunk_Manager *p_chunk_manager,
        World_Parameters *p_world_parameters,
        Signed_Index__i32 x__chunk, 
        Signed_Index__i32 y__chunk,
        Signed_Index__i32 z__chunk);

bool poll_chunk_manager_for__tile_collision(
        Chunk_Manager *p_chunk_manager,
        Entity *p_entity);

// TODO: prim wrap arguments
static Tile inline *get_tile_ptr_from__chunk_node(
        Chunk_Manager__Chunk_Map_Node *p_chunk_node,
        int32_t x__local, 
        int32_t y__local) {
#ifndef NDEBUG
    if (x__local < 0 
            || x__local >= CHUNK_WIDTH__IN_TILES
            || y__local < 0
            || y__local >= CHUNK_WIDTH__IN_TILES) {
        debug_error("get_tile_from__chunk_node out of bounds %d,%d", 
                x__local, y__local);
        return &p_chunk_node->p_chunk__here->tiles[0];
    }
#endif
    return &p_chunk_node->p_chunk__here->tiles[
        y__local * CHUNK_WIDTH__IN_TILES + x__local];
}

Tile *get_tile_ptr_from__chunk_manager_with__v__3i32F4(
        Chunk_Manager *p_chunk_manager,
        Vector__3i32F4 position);

#endif
