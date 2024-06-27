#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_chunk_manager(
        Chunk_Manager* p_chunk_manager,
        World_Parameters *p_world_parameters);

Index__u32 get_chunk_index_from__chunk_manager(
        Chunk_Manager *p_chunk_manager,
        Chunk_Vector__3i32 chunk_vector__3i32);

Chunk *get_p_chunk_from__chunk_manager_using__i32(
        Chunk_Manager *p_chunk_manager, 
        Signed_Index__i32 x__i32,
        Signed_Index__i32 y__i32,
        Signed_Index__i32 z__i32);

static Chunk inline *get_p_chunk_from__chunk_manager(
        Chunk_Manager *p_chunk_manager, 
        Chunk_Vector__3i32 chunk_vector__3i32) {
    return get_p_chunk_from__chunk_manager_using__i32(
            p_chunk_manager,
            chunk_vector__3i32.x__i32, 
            chunk_vector__3i32.y__i32, 
            chunk_vector__3i32.z__i32);
}

void move_chunk_manager(
        Chunk_Manager *p_chunk_manager,
        World_Parameters *p_world_parameters,
        Direction__u8 direction,
        Quantity__u32 steps);

bool poll_chunk_manager_for__chunk_movement(
        Chunk_Manager *p_chunk_manager,
        World_Parameters *p_world_parameters,
        Vector__3i32F4 position__3i32F4);

bool poll_chunk_manager_for__tile_collision(
        Chunk_Manager *p_chunk_manager,
        Entity *p_entity);

static Tile inline *get_p_tile_from__chunk_node(
        Chunk_Manager__Chunk_Map_Node *p_chunk_node,
        Local_Tile_Vector__3u8 local_tile_vector__3u8) {
#ifndef NDEBUG
    if (local_tile_vector__3u8.x__u8 < 0 
            || local_tile_vector__3u8.x__u8 >= CHUNK_WIDTH__IN_TILES
            || local_tile_vector__3u8.y__u8 < 0
            || local_tile_vector__3u8.y__u8 >= CHUNK_WIDTH__IN_TILES) {
        debug_error("get_tile_from__chunk_node out of bounds %d,%d", 
                local_tile_vector__3u8.x__u8, local_tile_vector__3u8.y__u8);
        return &p_chunk_node->p_chunk__here->tiles[0];
    }
#endif
    return &p_chunk_node->p_chunk__here->tiles[
        local_tile_vector__3u8.y__u8 
            * CHUNK_WIDTH__IN_TILES 
            + local_tile_vector__3u8.x__u8];
}

static Tile inline *get_p_tile_from__chunk_node_using__u8(
        Chunk_Manager__Chunk_Map_Node *p_chunk_node,
        Index__u8 x__u8,
        Index__u8 y__u8) {
#ifndef NDEBUG
    if (x__u8 < 0 
            || x__u8 >= CHUNK_WIDTH__IN_TILES
            || y__u8 < 0
            || y__u8 >= CHUNK_WIDTH__IN_TILES) {
        debug_error("get_tile_from__chunk_node out of bounds %d,%d", 
                x__u8, y__u8);
        return &p_chunk_node->p_chunk__here->tiles[0];
    }
#endif
    return &p_chunk_node->p_chunk__here->tiles[
        y__u8 
            * CHUNK_WIDTH__IN_TILES 
            + x__u8];
}

Tile *get_p_tile_from__chunk_manager(
        Chunk_Manager *p_chunk_manager,
        Vector__3i32F4 position);

Tile *get_p_tile_from__chunk_manager_with__3i32F4(
        Chunk_Manager *p_chunk_manager,
        Vector__3i32F4 position);

#endif
