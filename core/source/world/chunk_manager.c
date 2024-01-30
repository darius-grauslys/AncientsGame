#include <defines.h>
#include <world/chunk_manager.h>
#include <world/chunk.h>

void init_chunk_manager(
        Chunk_Manager* chunk_manager,
        World_Parameters *world_params) {
    chunk_manager->x__center_chunk =
        chunk_manager->y__center_chunk = 4;
    for (int32_t y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (int32_t x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            uint32_t index =
                get_chunk_index_during__initialization(x, y);
            Chunk_Manager__Chunk_Map_Node *chunk_map_node =
                &chunk_manager->chunk_map[index];

            Chunk *chunk__here =
                &chunk_manager->chunks[index];

            init_chunk(chunk__here, x, y);

            world_params->chunk_generator_f(world_params, chunk__here);

            chunk_map_node->chunk__here = chunk__here;

            // link north
            chunk_map_node->chunk_map_node__north =
                &chunk_manager->chunk_map[
                get_chunk_index_during__initialization(x, y + 1)
                ];

            // link east
            chunk_map_node->chunk_map_node__east =
                &chunk_manager->chunk_map[
                get_chunk_index_during__initialization(x + 1, y)
                ];

            // link south
            chunk_map_node->chunk_map_node__south =
                &chunk_manager->chunk_map[
                get_chunk_index_during__initialization(x, y - 1)
                ];

            // link west
            chunk_map_node->chunk_map_node__west =
                &chunk_manager->chunk_map[
                get_chunk_index_during__initialization(x - 1, y)
                ];
        }
    }

    chunk_manager->chunk_map_node__most_north_western =
        &chunk_manager->chunk_map[0];
}

uint32_t get_chunk_index_at__xyz_from__chunk_manager(
        Chunk_Manager *chunk_manager,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk) {
    // TODO: extend to use z

    Chunk *most_north_western__chunk =
        get_most_north_western__chunk(chunk_manager);
    Chunk *most_south_western__chunk =
        get_most_south_western__chunk(chunk_manager);

    if (x__chunk
            < most_north_western__chunk->x 
            || y__chunk
                > most_north_western__chunk->y 
            || x__chunk 
                > get_most_north_eastern__chunk(chunk_manager)->x
            || y__chunk
                < most_south_western__chunk->y) {
        // Deliberately do not print error.
        return 0;
    }

    int32_t local_x =
        x__chunk
        - most_north_western__chunk->x
        ;
    int32_t local_y =
        y__chunk
        - most_south_western__chunk->y
        ;

    return local_y 
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + local_x
        ;
}

void move_chunk_manager__chunks_north(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params) {
    int32_t x__old_most_north_western_chunk =
        get_most_north_eastern__chunk(chunk_manager)->x;
    int32_t y__new_most_north_western_chunk =
        get_most_north_western__chunk(chunk_manager)->y + 1;
    
    // move the NW north.
    move_most_north_western__chunk_map_node__north(chunk_manager);

    // Begin at NW
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        get_most_south_western__chunk_map_node(chunk_manager);

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
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params) {
    int32_t x__new_most_north_eastern_chunk =
        get_most_north_western__chunk(chunk_manager)->x + 1;
    int32_t y__old_most_south_eastern_chunk =
        get_most_south_eastern__chunk(chunk_manager)->y;

    // Move the NW east
    move_most_north_western__chunk_map_node__east(chunk_manager);

    // Begin at SE
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        get_most_south_eastern__chunk_map_node(chunk_manager);

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
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params) {
    int32_t x__old_most_south_western_chunk =
        get_most_south_western__chunk(chunk_manager)->x;
    int32_t y__new_most_south_western_chunk =
        get_most_south_western__chunk(chunk_manager)->y - 1;

    // Move the NW south
    move_most_north_western__chunk_map_node__south(chunk_manager);

    // Begin at SW
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        get_most_south_western__chunk_map_node(chunk_manager);

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
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params) {
    int32_t x__new_most_north_western_chunk =
        get_most_north_western__chunk(chunk_manager)->x - 1;
    int32_t y__old_most_south_western_chunk =
        get_most_south_western__chunk(chunk_manager)->y;

    // Move the NW west
    move_most_north_western__chunk_map_node__west(chunk_manager);

    // Begin SW
    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        get_most_south_western__chunk_map_node(chunk_manager);

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

void move_chunk_manager(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        Direction direction,
        uint32_t steps) {
    for (uint32_t step=0; step < steps; step++) {
        if (direction & DIRECTION__NORTH) {
            move_chunk_manager__chunks_north(
                    chunk_manager, 
                    world_params);
        }
        if (direction & DIRECTION__EAST) {
            move_chunk_manager__chunks_east(
                    chunk_manager, 
                    world_params);
        }
        if (direction & DIRECTION__SOUTH) {
            move_chunk_manager__chunks_south(
                    chunk_manager, 
                    world_params);
        }
        if (direction & DIRECTION__WEST) {
            move_chunk_manager__chunks_west(
                    chunk_manager, 
                    world_params);
        }
    }
}

bool poll_chunk_manager_for__chunk_movement(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk) {

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
        move_chunk_manager(
                chunk_manager, 
                world_params, 
                direction__move_chunks,
                1);
        return true;
    }

    return false;
}

Direction poll_chunk_manager_for__tile_collision(
        Chunk_Manager *chunk_manager, 
        Entity *entity) {
    
}

