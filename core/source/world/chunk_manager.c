#include "defines_weak.h"
#include "platform.h"
#include "platform_defines.h"
#include "serialization/serialization_request.h"
#include "serialization/serialized_field.h"
#include "world/serialization/world_directory.h"
#include "world/world.h"
#include <defines.h>
#include <stdbool.h>
#include <world/chunk.h>
#include <debug/debug.h>

#include <world/tile.h>
#include <collisions/hitbox_aabb.h>
#include <vectors.h>

#include <world/chunk_manager.h>
#include <world/chunk_vectors.h>
#include <world/tile_vectors.h>
#include <game.h>

///
/// Either loads or generates the chunk
///
void resolve_chunk(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

void initialize_chunk_manager(
        Game *p_game,
        Chunk_Manager *p_chunk_manager) {
    p_chunk_manager->x__center_chunk__signed_index_i32 =
        p_chunk_manager->y__center_chunk__signed_index_i32 = 0;
    for (Index__u32 index_of__chunk_map_node_ptr = 0;
            index_of__chunk_map_node_ptr
            < CHUNK_MANAGER__QUANTITY_OF_CHUNKS;
            index_of__chunk_map_node_ptr++) {
        p_chunk_manager->ptr_array_queue__serialized_nodes[
            index_of__chunk_map_node_ptr] = 0;
    }
    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Chunk_Manager__Chunk_Map_Node *p_chunk_map_node =
                &p_chunk_manager->chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Chunk *p_chunk__here =
                &p_chunk_manager->chunks[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                    + x];

            initialize_chunk(p_chunk__here);

            p_chunk_map_node->p_chunk__here = p_chunk__here;
            p_chunk_map_node->position_of__chunk_3i32 =
                get_vector__3i32(x,y,0);

            resolve_chunk(
                    p_game,
                    p_chunk_map_node);

            Index__u32 x__east, x__west, y__north, y__south;

            if (x == 0)
                x__west = CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1;
            else
                x__west = x - 1;
            if (x == CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1)
                x__east = 0;
            else
                x__east = x + 1;

            if (y == CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1)
                y__north = 0;
            else
                y__north = y + 1;
            if (y == 0)
                y__south = CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1;
            else
                y__south = y - 1;

            // link north
            p_chunk_map_node->p_north__chunk_map_node =
                &p_chunk_manager->chunk_map[
                y__north * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x
                ];

            // link east
            p_chunk_map_node->p_east__chunk_map_node =
                &p_chunk_manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x__east
                ];

            // link south
            p_chunk_map_node->p_south__chunk_map_node =
                &p_chunk_manager->chunk_map[
                y__south * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x 
                ];

            // link west
            p_chunk_map_node->p_west__chunk_map_node =
                &p_chunk_manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x__west
                ];
        }
    }

    p_chunk_manager->p_most_north_western__chunk_map_node =
        &p_chunk_manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        ];

    p_chunk_manager->p_most_north_eastern__chunk_map_node =
        &p_chunk_manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1
        ];

    p_chunk_manager->p_most_south_western__chunk_map_node =
        &p_chunk_manager->chunk_map[0];

    p_chunk_manager->p_most_south_eastern__chunk_map_node =
        &p_chunk_manager->chunk_map[
        GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1];
}

uint32_t get_chunk_index_from__chunk_manager(
        Chunk_Manager *p_chunk_manager,
        Chunk_Vector__3i32 chunk_vector__3i32) {
    // TODO: extend to use z

    if (chunk_vector__3i32.x__i32 < p_chunk_manager
            ->p_most_north_western__chunk_map_node
                ->position_of__chunk_3i32.x__i32
            || chunk_vector__3i32.y__i32 > p_chunk_manager
                ->p_most_north_western__chunk_map_node
                    ->position_of__chunk_3i32.y__i32
            || chunk_vector__3i32.x__i32 > p_chunk_manager
                ->p_most_south_eastern__chunk_map_node
                    ->position_of__chunk_3i32.x__i32
            || chunk_vector__3i32.y__i32 < p_chunk_manager
                ->p_most_south_eastern__chunk_map_node
                    ->position_of__chunk_3i32.y__i32) {
        debug_error("get_chunk_index_from__chunk_manager chunk index out of bounds: (%d, %d, %d)",
                chunk_vector__3i32.x__i32, 
                chunk_vector__3i32.y__i32, 
                chunk_vector__3i32.z__i32);
        debug_info("bounds are: (%d, %d) - (%d, %d)",
            p_chunk_manager->p_most_north_western__chunk_map_node
                ->position_of__chunk_3i32.x__i32,
            p_chunk_manager->p_most_north_western__chunk_map_node
                ->position_of__chunk_3i32.y__i32, 
            p_chunk_manager->p_most_south_eastern__chunk_map_node
                ->position_of__chunk_3i32.x__i32,
            p_chunk_manager->p_most_south_eastern__chunk_map_node
                ->position_of__chunk_3i32.y__i32);
        return 0;
    }

    Signed_Index__i32 local_x =
        chunk_vector__3i32.x__i32 - p_chunk_manager
        ->p_most_south_western__chunk_map_node
            ->position_of__chunk_3i32.x__i32;
    Signed_Index__i32 local_y =
        chunk_vector__3i32.y__i32 - p_chunk_manager
        ->p_most_south_western__chunk_map_node
            ->position_of__chunk_3i32.y__i32;

    return  local_y 
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + local_x;
}

Chunk* get_p_chunk_from__chunk_manager_using__i32(
        Chunk_Manager *p_chunk_manager, 
        Signed_Index__i32 x__chunk, 
        Signed_Index__i32 y__chunk, 
        Signed_Index__i32 z__chunk) {

    Signed_Index__i32 north_east__x = 
        p_chunk_manager
        ->p_most_north_eastern__chunk_map_node
        ->position_of__chunk_3i32.x__i32
        ;
    Signed_Index__i32 north_east__y = 
        p_chunk_manager
        ->p_most_north_eastern__chunk_map_node
        ->position_of__chunk_3i32.y__i32
        ;
    Signed_Index__i32 south_west__x = 
        p_chunk_manager
        ->p_most_south_western__chunk_map_node
        ->position_of__chunk_3i32.x__i32
        ;
    Signed_Index__i32 south_west__y = 
        p_chunk_manager
        ->p_most_south_western__chunk_map_node
        ->position_of__chunk_3i32.y__i32
        ;

    if (x__chunk < south_west__x
            || y__chunk > north_east__y
            || x__chunk > north_east__x
            || y__chunk < south_west__y) {
        debug_info("bounds are: (%d, %d) - (%d, %d)",
                south_west__x, south_west__y,
                north_east__x, north_east__y);
        debug_error("get_p_chunk_from__chunk_manager_using__i32, chunk index out of bounds: (%d, %d, %d)",
                x__chunk, y__chunk, z__chunk);
        return 0;
    }

    Chunk_Manager__Chunk_Map_Node *p_node =
        p_chunk_manager->p_most_south_western__chunk_map_node;
    for (Signed_Index__i32 x = south_west__x; x < x__chunk; x++) {
        p_node = p_node->p_east__chunk_map_node;
    }
    for (Signed_Index__i32 y = south_west__y; y < y__chunk; y++) {
        p_node = p_node->p_north__chunk_map_node;
    }

    return p_node->p_chunk__here;
}

void save_chunk(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *p_file_path_to__chunk) {
    Serialization_Request *p_serialization_request =
        PLATFORM_allocate_serialization_request(
                get_p_PLATFORM_file_system_context_from__game(p_game));
    if (!p_serialization_request) {
        debug_error("save_chunk failed to allocate serialization request.");
        clear_chunk_flags(p_chunk_map_node->p_chunk__here);
        set_chunk_as__visually_updated(p_chunk_map_node->p_chunk__here);
        return;
    }

    enum PLATFORM_Open_File_Error error =
        PLATFORM_open_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_file_path_to__chunk, 
                "wb", 
                p_serialization_request);

    set_serialization_request_as__fire_and_forget(p_serialization_request);
    if (!error) {
        // TODO: release p_serialization_request
        debug_error("save_chunk, error opening file: %d", 
                error);
        return;
    }

    set_serialization_request_as__using_serializer(
            p_serialization_request);
    set_serialization_request_as__write(
            p_serialization_request);
}

void load_chunk(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        char *p_file_path_to__chunk) {
    Serialization_Request *p_serialization_request =
        PLATFORM_allocate_serialization_request(
                get_p_PLATFORM_file_system_context_from__game(p_game));
    if (!p_serialization_request) {
        debug_error("load_chunk failed to allocate serialization request.");
        clear_chunk_flags(p_chunk_map_node->p_chunk__here);
        set_chunk_as__visually_updated(p_chunk_map_node->p_chunk__here);
        return;
    }

    enum PLATFORM_Open_File_Error error =
        PLATFORM_open_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_file_path_to__chunk, 
                "rb", 
                p_serialization_request);

    set_serialization_request_as__fire_and_forget(p_serialization_request);
    if (!error) {
        // TODO: release p_serialization_request
        debug_error("load_chunk, error opening file: %d", 
                error);
        return;
    }

    set_serialization_request_as__using_serializer(
            p_serialization_request);
    set_serialization_request_as__read(
            p_serialization_request);
}

void resolve_chunk(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    char file_path_to__chunk[128];
    memset(file_path_to__chunk, 0, sizeof(file_path_to__chunk));
    if (stat_chunk_file__tiles(
                p_game,
                p_chunk_map_node,
                file_path_to__chunk)) {
        load_chunk(
                p_game, 
                p_chunk_map_node,
                file_path_to__chunk);
        return;
    }

    get_p_world_parameters_from__game(p_game)
        ->f_chunk_generator(
            p_game, 
            p_chunk_map_node);
    // set_chunk_as__updated(p_chunk_map_node->p_chunk__here);
}

void enqueue_chunk_map_node_for__serialization(
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    Chunk_Manager__Chunk_Map_Node **p_chunk_map_node_ptr =
        p_chunk_manager->ptr_array_queue__serialized_nodes;

    Index__u32 index_of__chunk_map_node_ptr = 0;
    while (*p_chunk_map_node_ptr
            && index_of__chunk_map_node_ptr++
            < CHUNK_MANAGER__QUANTITY_OF_CHUNKS) {
        p_chunk_map_node_ptr++;
    }

#ifndef NDEBUG
    if (index_of__chunk_map_node_ptr
            >= CHUNK_MANAGER__QUANTITY_OF_CHUNKS) {
        debug_abort("enqueue_chunk_map_node_for__serialization, failed to enqueue: %d", index_of__chunk_map_node_ptr);
        return;
    }
#endif

    *p_chunk_map_node_ptr = 
        p_chunk_map_node;
}

void dequeue_chunk_map_node_for__serialization(
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    Chunk_Manager__Chunk_Map_Node **p_chunk_map_node_ptr =
        p_chunk_manager->ptr_array_queue__serialized_nodes;

    if (!*p_chunk_map_node_ptr)
        return;

    Chunk_Manager__Chunk_Map_Node **p_chunk_map_node_ptr_of__dequeue = 0;

    Index__u32 index_of__chunk_map_node_ptr = 0;
    do {
        if ((*p_chunk_map_node_ptr) == p_chunk_map_node)
            p_chunk_map_node_ptr_of__dequeue =
                p_chunk_map_node_ptr;
    } while (index_of__chunk_map_node_ptr++
            < CHUNK_MANAGER__QUANTITY_OF_CHUNKS
            && *(++p_chunk_map_node_ptr));
    p_chunk_map_node_ptr--;

#ifndef NDEBUG
    if (!p_chunk_map_node_ptr_of__dequeue) {
        debug_abort("dequeue_chunk_map_node_for__serialization, failed to dequeue.");
        return;
    }
#endif

    *p_chunk_map_node_ptr_of__dequeue =
        *p_chunk_map_node_ptr;
    *p_chunk_map_node_ptr = 0;
}

bool poll_chunk_manager_for__serialization(
        Game *p_game,
        Chunk_Manager *p_chunk_manager) {
    Chunk_Manager__Chunk_Map_Node **p_chunk_map_node_ptr =
        p_chunk_manager->ptr_array_queue__serialized_nodes;

    if (!*p_chunk_map_node_ptr) {
        return false;
    }

    Index__u32 index_of__chunk_map_node_ptr = 0;
    do {
skip:
        ;
        Chunk *p_chunk =
            (*p_chunk_map_node_ptr)->p_chunk__here;
        if (!is_chunk__awaiting_serialization(p_chunk)) {
            dequeue_chunk_map_node_for__serialization(
                    p_chunk_manager, 
                    *p_chunk_map_node_ptr);
            if (*p_chunk_map_node_ptr)
                goto skip;
        }
    } while (++index_of__chunk_map_node_ptr
            < CHUNK_MANAGER__QUANTITY_OF_CHUNKS
            && !*(++p_chunk_map_node_ptr));
    return (bool)(p_chunk_manager->ptr_array_queue__serialized_nodes[0]);
}

void replace_chunk(
        Game *p_game,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node,
        i32 x__new,
        i32 y__new) {

    if (is_chunk__updated(p_chunk_map_node->p_chunk__here)) {
        enqueue_chunk_map_node_for__serialization(
                get_p_chunk_manager_from__game(p_game), 
                p_chunk_map_node);
        char file_path_to__chunk[128];
        memset(file_path_to__chunk, 0, sizeof(file_path_to__chunk));
        Quantity__u8 length_of__path_to__chunk =
            stat_chunk_directory(
                    p_game,
                    p_chunk_map_node,
                    file_path_to__chunk);
        if (length_of__path_to__chunk) {
            if (append_chunk_file__tiles_to__path(
                    file_path_to__chunk, 
                    length_of__path_to__chunk, 
                    sizeof(file_path_to__chunk))) {
                save_chunk(
                        p_game, 
                        p_chunk_map_node,
                        file_path_to__chunk);
            } else {
                debug_error("replace_chunk, failed to append to path.");
                goto fail_save;
            }
        } else {
fail_save:
            clear_chunk_flags(p_chunk_map_node->p_chunk__here);
        }
    }

    p_chunk_map_node->position_of__chunk_3i32.x__i32 = x__new;
    p_chunk_map_node->position_of__chunk_3i32.y__i32 = y__new;

    if (!is_chunk__updated(p_chunk_map_node->p_chunk__here)) {
        resolve_chunk(
                p_game, 
                p_chunk_map_node);
    }
}

// TODO: find a way to consolidate this helpers without macros?
void move_chunk_manager__chunks_north(
    Game *p_game,
    Chunk_Manager *p_chunk_manager) {
    Signed_Index__i32 x__old_most_north_western_chunk =
        p_chunk_manager->p_most_north_western__chunk_map_node
            ->position_of__chunk_3i32.x__i32;
    Signed_Index__i32 y__new_most_north_western_chunk =
        p_chunk_manager->p_most_north_western__chunk_map_node
            ->position_of__chunk_3i32.y__i32 + 1;
    p_chunk_manager->p_most_north_western__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node
            ->p_north__chunk_map_node;
    p_chunk_manager->p_most_north_eastern__chunk_map_node =
        p_chunk_manager->p_most_north_eastern__chunk_map_node
            ->p_north__chunk_map_node;
    p_chunk_manager->p_most_south_western__chunk_map_node =
        p_chunk_manager->p_most_south_western__chunk_map_node
            ->p_north__chunk_map_node;
    p_chunk_manager->p_most_south_eastern__chunk_map_node =
            p_chunk_manager->p_most_south_eastern__chunk_map_node
                ->p_north__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node;

    for (Quantity__u32 step = 0; 
            step < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
            step++) {
        if (p_current__chunk_map_node
                ->position_of__chunk_3i32.x__i32 !=
                (x__old_most_north_western_chunk + step)
                || p_current__chunk_map_node
                    ->position_of__chunk_3i32.y__i32 
                != y__new_most_north_western_chunk) {

            replace_chunk(
                    p_game,
                    p_current__chunk_map_node,
                    x__old_most_north_western_chunk + step,
                    y__new_most_north_western_chunk
                    );
        }

        p_current__chunk_map_node = 
            p_current__chunk_map_node->p_east__chunk_map_node;
    }
}

void move_chunk_manager__chunks_east(
        Game *p_game,
        Chunk_Manager *p_chunk_manager) {
    int32_t x__new_most_north_eastern_chunk =
        p_chunk_manager->p_most_north_eastern__chunk_map_node
            ->position_of__chunk_3i32.x__i32 + 1;
    int32_t y__old_most_south_eastern_chunk =
        p_chunk_manager->p_most_south_eastern__chunk_map_node
            ->position_of__chunk_3i32.y__i32;

    p_chunk_manager->p_most_north_western__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node
            ->p_east__chunk_map_node;
    p_chunk_manager->p_most_north_eastern__chunk_map_node =
        p_chunk_manager->p_most_north_eastern__chunk_map_node
            ->p_east__chunk_map_node;
    p_chunk_manager->p_most_south_western__chunk_map_node =
        p_chunk_manager->p_most_south_western__chunk_map_node
            ->p_east__chunk_map_node;
    p_chunk_manager->p_most_south_eastern__chunk_map_node =
        p_chunk_manager->p_most_south_eastern__chunk_map_node
            ->p_east__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_south_eastern__chunk_map_node;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            step++) {
        if (p_current__chunk_map_node
                ->position_of__chunk_3i32.x__i32 !=
                x__new_most_north_eastern_chunk
                || (p_current__chunk_map_node
                    ->position_of__chunk_3i32.y__i32 != 
                    y__old_most_south_eastern_chunk + step)) {

            replace_chunk(
                    p_game,
                    p_current__chunk_map_node,
                    x__new_most_north_eastern_chunk,
                    y__old_most_south_eastern_chunk + step
                    );
        }

        p_current__chunk_map_node = 
            p_current__chunk_map_node->p_north__chunk_map_node;
    }
}

void move_chunk_manager__chunks_south(
        Game *p_game,
        Chunk_Manager *p_chunk_manager) {
    int32_t x__old_most_south_western_chunk=
        p_chunk_manager->p_most_south_western__chunk_map_node
            ->position_of__chunk_3i32.x__i32;
    int32_t y__new_most_south_western_chunk=
        p_chunk_manager->p_most_south_western__chunk_map_node
            ->position_of__chunk_3i32.y__i32 - 1;
    p_chunk_manager->p_most_north_western__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node
            ->p_south__chunk_map_node;
    p_chunk_manager->p_most_north_eastern__chunk_map_node =
        p_chunk_manager->p_most_north_eastern__chunk_map_node
            ->p_south__chunk_map_node;
    p_chunk_manager->p_most_south_western__chunk_map_node =
        p_chunk_manager->p_most_south_western__chunk_map_node
            ->p_south__chunk_map_node;
    p_chunk_manager->p_most_south_eastern__chunk_map_node =
        p_chunk_manager->p_most_south_eastern__chunk_map_node
            ->p_south__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_south_western__chunk_map_node;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
            step++) {
        if (p_current__chunk_map_node
                ->position_of__chunk_3i32.x__i32 !=
                (x__old_most_south_western_chunk + step)
                || p_current__chunk_map_node
                ->position_of__chunk_3i32.y__i32 
                != y__new_most_south_western_chunk) {

            replace_chunk(
                    p_game,
                    p_current__chunk_map_node,
                    x__old_most_south_western_chunk + step,
                    y__new_most_south_western_chunk
                    );
        }

        p_current__chunk_map_node = 
            p_current__chunk_map_node->p_east__chunk_map_node;
    }
}

void move_chunk_manager__chunks_west(
        Game *p_game,
        Chunk_Manager *p_chunk_manager) {
    int32_t x__new_most_north_western_chunk =
        p_chunk_manager->p_most_north_western__chunk_map_node
            ->position_of__chunk_3i32.x__i32 - 1;
    int32_t y__old_most_south_western_chunk =
        p_chunk_manager->p_most_south_western__chunk_map_node
            ->position_of__chunk_3i32.y__i32;

    p_chunk_manager->p_most_north_western__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node
            ->p_west__chunk_map_node;
    p_chunk_manager->p_most_north_eastern__chunk_map_node =
        p_chunk_manager->p_most_north_eastern__chunk_map_node
            ->p_west__chunk_map_node;
    p_chunk_manager->p_most_south_western__chunk_map_node =
        p_chunk_manager->p_most_south_western__chunk_map_node
            ->p_west__chunk_map_node;
    p_chunk_manager->p_most_south_eastern__chunk_map_node =
        p_chunk_manager->p_most_south_eastern__chunk_map_node
            ->p_west__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_south_western__chunk_map_node;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            step++) {
        if (p_current__chunk_map_node
                ->position_of__chunk_3i32.x__i32 !=
                x__new_most_north_western_chunk
                || (p_current__chunk_map_node
                    ->position_of__chunk_3i32.y__i32 != 
                    y__old_most_south_western_chunk + step)) {

            replace_chunk(
                    p_game,
                    p_current__chunk_map_node,
                    x__new_most_north_western_chunk,
                    y__old_most_south_western_chunk + step
                    );
        }

        p_current__chunk_map_node = 
            p_current__chunk_map_node->p_north__chunk_map_node;
    }
}

void move_chunk_manager(
        Game *p_game,
        Chunk_Manager *p_chunk_manager,
        Direction__u8 direction,
        Quantity__u32 steps) {
    for (Quantity__u32 step=0; step < steps; step++) {
        if (direction & DIRECTION__NORTH) {
            move_chunk_manager__chunks_north(
                    p_game,
                    p_chunk_manager);
        }
        if (direction & DIRECTION__EAST) {
            move_chunk_manager__chunks_east(
                    p_game,
                    p_chunk_manager);
        }
        if (direction & DIRECTION__SOUTH) {
            move_chunk_manager__chunks_south(
                    p_game,
                    p_chunk_manager);
        }
        if (direction & DIRECTION__WEST) {
            move_chunk_manager__chunks_west(
                    p_game,
                    p_chunk_manager);
        }
    }
}

bool poll_chunk_manager_for__chunk_movement(
        Game *p_game,
        Chunk_Manager *p_chunk_manager,
        Vector__3i32F4 position__3i32F4) {

    Chunk_Vector__3i32 chunk_vector__3i32 =
        vector_3i32F4_to__chunk_vector_3i32(position__3i32F4);

    Direction__u8 direction__move_chunks = DIRECTION__NONE;

    if (chunk_vector__3i32.x__i32 
            != p_chunk_manager->x__center_chunk__signed_index_i32 
            || chunk_vector__3i32.y__i32 
            != p_chunk_manager->y__center_chunk__signed_index_i32) {
        if (p_chunk_manager->x__center_chunk__signed_index_i32 
                < chunk_vector__3i32.x__i32) {
            direction__move_chunks |=
                DIRECTION__EAST;
        } else if (p_chunk_manager->x__center_chunk__signed_index_i32 
                > chunk_vector__3i32.x__i32) {
            direction__move_chunks |=
                DIRECTION__WEST;
        }
        if (p_chunk_manager->y__center_chunk__signed_index_i32 
                < chunk_vector__3i32.y__i32) {
            direction__move_chunks |=
                DIRECTION__NORTH;
        } else if (p_chunk_manager->y__center_chunk__signed_index_i32 
                > chunk_vector__3i32.y__i32) {
            direction__move_chunks |=
                DIRECTION__SOUTH;
        }
        p_chunk_manager->x__center_chunk__signed_index_i32 = 
            chunk_vector__3i32.x__i32;
        p_chunk_manager->y__center_chunk__signed_index_i32 = 
            chunk_vector__3i32.y__i32;
    }

    if(direction__move_chunks != DIRECTION__NONE) {
        move_chunk_manager(
                p_game,
                p_chunk_manager, 
                direction__move_chunks,
                1);
        return true;
    }

    return false;
}

bool poll_chunk_manager_for__tile_collision(
        Chunk_Manager *p_chunk_manager, 
        Entity *p_entity) {
    if (p_entity->hitbox.velocity__3i32F4.x__i32F4 == 0
            && p_entity->hitbox.velocity__3i32F4.y__i32F4 == 0) {
        return true;
    }

    Vector__3i32F4 aa, bb;
    get_aa_bb_as__vectors_3i32F4_from__hitbox(
            &p_entity->hitbox, &aa, &bb);

    //TODO: magic num
    i32F4 chunk_xy_vectors[8] = {
        get_chunk_x_i32_from__vector_3i32F4(aa),
        get_chunk_y_i32_from__vector_3i32F4(aa),
        get_chunk_x_i32_from__vector_3i32F4(bb),
        get_chunk_y_i32_from__vector_3i32F4(aa),
        get_chunk_x_i32_from__vector_3i32F4(aa),
        get_chunk_y_i32_from__vector_3i32F4(bb),
        get_chunk_x_i32_from__vector_3i32F4(bb),
        get_chunk_y_i32_from__vector_3i32F4(bb),
    };
    Signed_Index__i32 local_positions[8] = {
        get_tile_x_u8_from__vector_3i32F4(aa),
        get_tile_y_u8_from__vector_3i32F4(aa),
        get_tile_x_u8_from__vector_3i32F4(bb),
        get_tile_y_u8_from__vector_3i32F4(aa),
        get_tile_x_u8_from__vector_3i32F4(aa),
        get_tile_y_u8_from__vector_3i32F4(bb),
        get_tile_x_u8_from__vector_3i32F4(bb),
        get_tile_y_u8_from__vector_3i32F4(bb),
    };
    Signed_Index__i32 corner_positions[8] = {
        i32F4_to__i32(aa.x__i32F4), i32F4_to__i32(aa.y__i32F4),
        i32F4_to__i32(bb.x__i32F4), i32F4_to__i32(aa.y__i32F4),
        i32F4_to__i32(aa.x__i32F4), i32F4_to__i32(bb.y__i32F4),
        i32F4_to__i32(bb.x__i32F4), i32F4_to__i32(bb.y__i32F4)
    };
    Direction__u8 directions[4] = {
        DIRECTION__SOUTH_EAST,
        DIRECTION__SOUTH_WEST,
        DIRECTION__NORTH_EAST,
        DIRECTION__NORTH_WEST
    };

    for (Index__u32 index=0;index<8;index+=2) {
        Signed_Index__i32 x__chunk =
            chunk_xy_vectors[index]; //entity->hitbox.x__chunk;
        Signed_Index__i32 y__chunk =
            chunk_xy_vectors[index+1]; //entity->hitbox.y__chunk;

        Chunk *p_chunk =
            get_p_chunk_from__chunk_manager_using__i32(
                    p_chunk_manager,
                    x__chunk,
                    y__chunk,
                    0);

        if (!p_chunk) {
            debug_warning__verbose("poll_chunk_manager_for__tile_collision, entity out of tile collision bounds.");
            debug_warning__verbose("access attempt: %d, %d",
                    x__chunk, y__chunk);
            return false;
        }

        Tile *p_tile =
            get_p_tile_from__chunk_using__u8(
                    p_chunk,
                    local_positions[index],
                    local_positions[index+1],
                    0);

        if (is_tile__unpassable(p_tile)) {
            if (p_entity->m_entity_tile_collision_handler) {
                p_entity->m_entity_tile_collision_handler(
                        p_entity,
                        p_tile,
                        corner_positions[index],
                        corner_positions[index+1],
                        directions[index>>2]);
            }
        }
    }

    return true;
}

Tile *get_p_tile_from__chunk_manager_with__3i32F4(
        Chunk_Manager *p_chunk_manager,
        Vector__3i32F4 position) {

    Vector__3i32 chunk_index =
        vector_3i32F4_to__chunk_vector_3i32(position);
    Vector__3u8 local_position =
        vector_3i32F4_to__local_tile_vector_3u8(
                position);

    Chunk *p_chunk =
        get_p_chunk_from__chunk_manager(
                p_chunk_manager, 
                chunk_index);
#ifndef NDEBUG
    if (!p_chunk) {
        debug_warning("nullptr: get_p_tile_from__chunk_manager_with__3i32F4");
        return 0;
    }
#endif
    Tile *p_tile =
        get_p_tile_from__chunk(
                p_chunk, 
                local_position);

    return p_tile;
}

Tile *get_p_tile_from__chunk_manager_with__ray_3i32F20(
        Chunk_Manager *p_chunk_manager,
        Ray__3i32F20 *p_ray__3i32F20) {
    Vector__3i32F4 tile_pos = 
        vector_3i32F20_to__vector_3i32F4(
                p_ray__3i32F20->ray_current_vector__3i32F20);
    Chunk *p_chunk =
        get_p_chunk_from__chunk_manager_using__i32(
                p_chunk_manager,
                get_chunk_x_i32_from__vector_3i32F4(tile_pos),
                get_chunk_y_i32_from__vector_3i32F4(tile_pos),
                0);

    if (!p_chunk) {
        return 0;
    }
    return
        get_p_tile_from__chunk_using__u8(
                p_chunk,
                get_tile_x_u8_from__vector_3i32F4(tile_pos),
                get_tile_y_u8_from__vector_3i32F4(tile_pos),
                0);
}

