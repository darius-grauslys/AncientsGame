#include <defines.h>
#include <world/chunk.h>
#include <debug/debug.h>

void init_chunk_manager(
        Chunk_Manager* manager,
        World_Parameters *world_params) {
    manager->x__center_chunk =
        manager->y__center_chunk = 0;
    for (int32_t y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (int32_t x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Chunk_Manager__Chunk_Map_Node *chunk_map_node =
                &manager->chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Chunk *chunk__here =
                &manager->chunks[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                    + x];

            init_chunk(chunk__here, x, -y);

            world_params->chunk_generator_f(world_params, chunk__here);

            chunk_map_node->chunk__here = chunk__here;

            uint32_t x__east, x__west, y__north, y__south;

            if (x == 0)
                x__west = CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1;
            else
                x__west = x - 1;
            if (x == CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1)
                x__east = 0;
            else
                x__east = x + 1;

            if (y == 0)
                y__north = CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1;
            else
                y__north = y - 1;
            if (y == CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1)
                y__south = 0;
            else
                y__south = y + 1;

            // link north
            chunk_map_node->chunk_map_node__north =
                &manager->chunk_map[
                y__north * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x
                ];

            // link east
            chunk_map_node->chunk_map_node__east =
                &manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x__east
                ];

            // link south
            chunk_map_node->chunk_map_node__south =
                &manager->chunk_map[
                y__south * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x 
                ];

            // link west
            chunk_map_node->chunk_map_node__west =
                &manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x__west
                ];
        }
    }

    manager->chunk_map_node__most_north_western =
        &manager->chunk_map[0];

    manager->chunk_map_node__most_north_eastern =
        &manager->chunk_map[
        GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1];

    manager->chunk_map_node__most_south_western =
        &manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW];

    manager->chunk_map_node__most_south_eastern =
        &manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1
        ];
}

Chunk* get_chunk_from__chunk_manager(
        Chunk_Manager* manager, 
        int32_t global_chunk_x, int32_t global_chunk_y, 
        int32_t global_chunk_z) {
    debug_warning("get_chunk_from__chunk_manager doesn't use \
            global_chunk_z yet.");

    if (global_chunk_x < manager->chunk_map_node__most_north_western->chunk__here->x 
            || global_chunk_y > manager->chunk_map_node__most_north_western->chunk__here->y 
            || global_chunk_x > manager->chunk_map_node__most_south_eastern->chunk__here->x
            || global_chunk_y < manager->chunk_map_node__most_south_eastern->chunk__here->y) {
        debug_error("chunk index out of bounds: (%d, %d)",
                global_chunk_x, global_chunk_y);
        return &manager->chunks[0];
    }

    int32_t local_x =
        global_chunk_x - manager->chunk_map_node__most_north_western->chunk__here->x;
    int32_t local_y =
        global_chunk_y - manager->chunk_map_node__most_south_eastern->chunk__here->y;

    return &manager->chunks[
        local_y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
            + local_x
    ];
}

void move_chunk_manager__chunks_north(
        Chunk_Manager *manager,
        World_Parameters *world_params) {
    int32_t x__old_most_north_western_chunk =
        manager->chunk_map_node__most_north_western
            ->chunk__here->x;
    int32_t y__new_most_north_western_chunk =
        manager->chunk_map_node__most_north_western
            ->chunk__here->y + 1;
    manager->chunk_map_node__most_north_western =
        manager->chunk_map_node__most_north_western->chunk_map_node__north;
    manager->chunk_map_node__most_north_eastern =
        manager->chunk_map_node__most_north_eastern->chunk_map_node__north;
    manager->chunk_map_node__most_south_western =
        manager->chunk_map_node__most_south_western->chunk_map_node__north;
    manager->chunk_map_node__most_south_eastern =
        manager->chunk_map_node__most_south_eastern->chunk_map_node__north;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        manager->chunk_map_node__most_north_western;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x !=
                (x__old_most_north_western_chunk + step)
                || chunk__here->y != y__new_most_north_western_chunk) {

            chunk__here->x =
                x__old_most_north_western_chunk + step;
            chunk__here->y =
                y__new_most_north_western_chunk;

            world_params->chunk_generator_f(
                    world_params,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->chunk_map_node__east;
    }
}

void move_chunk_manager__chunks_east(
        Chunk_Manager *manager,
        World_Parameters *world_params) {
    int32_t x__new_most_north_eastern_chunk =
        manager->chunk_map_node__most_north_eastern
            ->chunk__here->x + 1;
    int32_t y__old_most_south_eastern_chunk =
        manager->chunk_map_node__most_south_eastern
            ->chunk__here->y;

    manager->chunk_map_node__most_north_western =
        manager->chunk_map_node__most_north_western->chunk_map_node__east;
    manager->chunk_map_node__most_north_eastern =
        manager->chunk_map_node__most_north_eastern->chunk_map_node__east;
    manager->chunk_map_node__most_south_western =
        manager->chunk_map_node__most_south_western->chunk_map_node__east;
    manager->chunk_map_node__most_south_eastern =
        manager->chunk_map_node__most_south_eastern->chunk_map_node__east;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        manager->chunk_map_node__most_south_eastern;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x !=
                x__new_most_north_eastern_chunk
                || (chunk__here->y != 
                    y__old_most_south_eastern_chunk + step)) {

            chunk__here->x =
                x__new_most_north_eastern_chunk;
            chunk__here->y =
                y__old_most_south_eastern_chunk + step;

            world_params->chunk_generator_f(
                    world_params,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->chunk_map_node__north;
    }
}

void move_chunk_manager__chunks_south(
        Chunk_Manager *manager,
        World_Parameters *world_params) {
    int32_t x__old_most_south_western_chunk =
        manager->chunk_map_node__most_south_western
            ->chunk__here->x;
    int32_t y__new_most_south_western_chunk =
        manager->chunk_map_node__most_south_western
            ->chunk__here->y - 1;
    manager->chunk_map_node__most_north_western =
        manager->chunk_map_node__most_north_western->chunk_map_node__south;
    manager->chunk_map_node__most_north_eastern =
        manager->chunk_map_node__most_north_eastern->chunk_map_node__south;
    manager->chunk_map_node__most_south_western =
        manager->chunk_map_node__most_south_western->chunk_map_node__south;
    manager->chunk_map_node__most_south_eastern =
        manager->chunk_map_node__most_south_eastern->chunk_map_node__south;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        manager->chunk_map_node__most_south_western;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x !=
                (x__old_most_south_western_chunk + step)
                || chunk__here->y != y__new_most_south_western_chunk) {

            chunk__here->x =
                x__old_most_south_western_chunk + step;
            chunk__here->y =
                y__new_most_south_western_chunk;

            world_params->chunk_generator_f(
                    world_params,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->chunk_map_node__east;
    }
}

void move_chunk_manager__chunks_west(
        Chunk_Manager *manager,
        World_Parameters *world_params) {
    int32_t x__new_most_north_western_chunk =
        manager->chunk_map_node__most_north_western
            ->chunk__here->x - 1;
    int32_t y__old_most_south_western_chunk =
        manager->chunk_map_node__most_south_western
            ->chunk__here->y;

    manager->chunk_map_node__most_north_western =
        manager->chunk_map_node__most_north_western->chunk_map_node__west;
    manager->chunk_map_node__most_north_eastern =
        manager->chunk_map_node__most_north_eastern->chunk_map_node__west;
    manager->chunk_map_node__most_south_western =
        manager->chunk_map_node__most_south_western->chunk_map_node__west;
    manager->chunk_map_node__most_south_eastern =
        manager->chunk_map_node__most_south_eastern->chunk_map_node__west;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        manager->chunk_map_node__most_south_western;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x !=
                x__new_most_north_western_chunk
                || (chunk__here->y != 
                    y__old_most_south_western_chunk + step)) {

            chunk__here->x =
                x__new_most_north_western_chunk;
            chunk__here->y =
                y__old_most_south_western_chunk + step;

            world_params->chunk_generator_f(
                    world_params,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->chunk_map_node__north;
    }
}

void move_chunk_manager__chunks(
        Chunk_Manager *manager,
        World_Parameters *world_params,
        Direction direction,
        uint32_t steps) {
    for (uint32_t step=0; step < steps; step++) {
        if (direction & DIRECTION__NORTH) {
            move_chunk_manager__chunks_north(
                    manager, 
                    world_params);
        }
        if (direction & DIRECTION__EAST) {
            move_chunk_manager__chunks_east(
                    manager, 
                    world_params);
        }
        if (direction & DIRECTION__SOUTH) {
            move_chunk_manager__chunks_south(
                    manager, 
                    world_params);
        }
        if (direction & DIRECTION__WEST) {
            move_chunk_manager__chunks_west(
                    manager, 
                    world_params);
        }
    }
}

bool poll_chunk_manager__for_chunk_movement(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        int32_t x__chunk, int32_t y__chunk) {

    Direction direction__move_chunks = DIRECTION__NONE;

    if (x__chunk != chunk_manager->x__center_chunk 
        || y__chunk != chunk_manager->y__center_chunk) {
        if (chunk_manager->x__center_chunk < x__chunk) {
            direction__move_chunks |=
                DIRECTION__EAST;
        } else if (chunk_manager->x__center_chunk > x__chunk) {
            direction__move_chunks |=
                DIRECTION__WEST;
        }
        if (chunk_manager->y__center_chunk > y__chunk) {
            direction__move_chunks |=
                DIRECTION__NORTH;
        } else if (chunk_manager->y__center_chunk < y__chunk) {
            direction__move_chunks |=
                DIRECTION__SOUTH;
        }
        chunk_manager->x__center_chunk = x__chunk;
        chunk_manager->y__center_chunk = y__chunk;
    }

    if(direction__move_chunks != DIRECTION__NONE) {
        move_chunk_manager__chunks(
                chunk_manager, 
                world_params, 
                direction__move_chunks,
                1);
        return true;
    }

    return false;
}
