#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <defines.h>

static Chunk_Manager__Chunk_Map_Node inline
*get_most_north_western__chunk_map_node(
        Chunk_Manager *chunk_manager) {
    return chunk_manager->chunk_map_node__most_north_western;
}

static Chunk_Manager__Chunk_Map_Node inline
*get_most_north_eastern__chunk_map_node(
        Chunk_Manager *chunk_manager) {
    return chunk_manager
        ->chunk_map_node__most_north_western
        ->chunk_map_node__west;
}

static Chunk_Manager__Chunk_Map_Node inline
*get_most_south_western__chunk_map_node(
        Chunk_Manager *chunk_manager) {
    return chunk_manager
        ->chunk_map_node__most_north_western
        ->chunk_map_node__north;
}

static Chunk_Manager__Chunk_Map_Node inline
*get_most_south_eastern__chunk_map_node(
        Chunk_Manager *chunk_manager) {
    return chunk_manager
        ->chunk_map_node__most_north_western
        ->chunk_map_node__north
        ->chunk_map_node__west;
}

static Chunk inline *get_most_north_western__chunk(
        Chunk_Manager *chunk_manager) {
    return get_most_north_western__chunk_map_node(
            chunk_manager)
        ->chunk__here;
}

static Chunk inline *get_most_north_eastern__chunk(
        Chunk_Manager *chunk_manager) {
    return get_most_north_eastern__chunk_map_node(
            chunk_manager)
        ->chunk__here;
}

static Chunk inline *get_most_south_western__chunk(
        Chunk_Manager *chunk_manager) {
    return get_most_south_western__chunk_map_node(
            chunk_manager)
        ->chunk__here;
}

static Chunk inline *get_most_south_eastern__chunk(
        Chunk_Manager *chunk_manager) {
    return get_most_south_eastern__chunk_map_node(
            chunk_manager)
        ->chunk__here;
}

static void inline move_most_north_western__chunk_map_node__north(
        Chunk_Manager *chunk_manager) {
    chunk_manager->chunk_map_node__most_north_western =
        get_most_south_western__chunk_map_node(chunk_manager);
}

static void inline move_most_north_western__chunk_map_node__east(
        Chunk_Manager *chunk_manager) {
    chunk_manager->chunk_map_node__most_north_western =
        chunk_manager
        ->chunk_map_node__most_north_western
        ->chunk_map_node__east
        ;
}

static void inline move_most_north_western__chunk_map_node__west(
        Chunk_Manager *chunk_manager) {
    chunk_manager->chunk_map_node__most_north_western =
        get_most_north_eastern__chunk_map_node(chunk_manager);
}

static void inline move_most_north_western__chunk_map_node__south(
        Chunk_Manager *chunk_manager) {
    chunk_manager->chunk_map_node__most_north_western =
        chunk_manager
        ->chunk_map_node__most_north_western
        ->chunk_map_node__south
        ;
}

void init_chunk_manager(
        Chunk_Manager* chunk_manager,
        World_Parameters *world_params);

uint32_t get_chunk_index_at__xyz_from__chunk_manager(
        Chunk_Manager *chunk_manager,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk);

///
/// This will not print out an error
/// if the chunk is unable to be found.
/// It will return nullptr instead.
///
/// Be sure that your coordinates are
/// in bounds of the chunk_manager,
/// or otherwise check the return value
/// to be not nullptr.
///
static Chunk inline *get_chunk_from__chunk_manager(
        Chunk_Manager *chunk_manager, 
        int32_t x__chunk, int32_t y__chunk, 
        int32_t z__chunk) {

    return &chunk_manager->chunks[
        get_chunk_index_at__xyz_from__chunk_manager(
                chunk_manager,
                x__chunk, y__chunk,
                z__chunk)
    ];
}

static Chunk_Manager__Chunk_Map_Node inline 
*get_chunk_map_node_from__chunk_manager(
        Chunk_Manager *chunk_manager, 
        int32_t x__chunk, int32_t y__chunk, 
        int32_t z__chunk) {

    //TODO: include z
    return &chunk_manager->chunk_map[
        get_chunk_index_during__initialization(
            get_chunk_mod_index(
                x__chunk
                ),
            get_chunk_mod_index(
                y__chunk
                )
            )
    ];
}

#ifdef DEBUG_H
///
/// Use this if you want to (and should unless with
/// good reason) print an error if chunk acquisition
/// is out of bounds.
///
void debug_error(const char *msg_fmt, ...);
static Chunk inline *get_chunk_from__chunk_manager__verbose(
        Chunk_Manager *chunk_manager,
        int32_t x__chunk,
        int32_t y__chunk,
        int32_t z__chunk) {
    Chunk *chunk = get_chunk_from__chunk_manager(
            chunk_manager,
            x__chunk,
            y__chunk,
            z__chunk);
    if (!chunk) {
        debug_error("get_chunk_from__chunk_manager__verbose out of bounds: \
(%d, %d, %d)", x__chunk, y__chunk, z__chunk);
    }

    return chunk;
}
#endif

void move_chunk_manager(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        Direction direction,
        uint32_t steps);

void set_chunk_manager_at__position(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        int32_t x__chunk,
        int32_t y__chunk);

bool poll_chunk_manager_for__chunk_movement(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk);

#endif
