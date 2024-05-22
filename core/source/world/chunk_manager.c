#include <defines.h>
#include <world/chunk.h>
#include <debug/debug.h>

#include <world/tile.h>
#include <collisions/hitbox_aabb.h>

void init_chunk_manager(
        Chunk_Manager* chunk_manager,
        World_Parameters *world_params) {
    chunk_manager->x__center_chunk =
        chunk_manager->y__center_chunk = 0;
    for (int32_t y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (int32_t x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Chunk_Manager__Chunk_Map_Node *chunk_map_node =
                &chunk_manager->chunk_map[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            Chunk *chunk__here =
                &chunk_manager->chunks[
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
                &chunk_manager->chunk_map[
                y__north * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x
                ];

            // link east
            chunk_map_node->chunk_map_node__east =
                &chunk_manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x__east
                ];

            // link south
            chunk_map_node->chunk_map_node__south =
                &chunk_manager->chunk_map[
                y__south * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x 
                ];

            // link west
            chunk_map_node->chunk_map_node__west =
                &chunk_manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x__west
                ];
        }
    }

    chunk_manager->chunk_map_node__most_north_western =
        &chunk_manager->chunk_map[0];

    chunk_manager->chunk_map_node__most_north_eastern =
        &chunk_manager->chunk_map[
        GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1];

    chunk_manager->chunk_map_node__most_south_western =
        &chunk_manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW];

    chunk_manager->chunk_map_node__most_south_eastern =
        &chunk_manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1
        ];
}

uint32_t get_chunk_index_at__xyz_from__chunk_manager(
        Chunk_Manager *chunk_manager,
        int32_t x__chunk, int32_t y__chunk,
        int32_t z__chunk) {
    // TODO: extend to use z

    if (x__chunk < chunk_manager
            ->chunk_map_node__most_north_western->chunk__here->x 
            || y__chunk > chunk_manager
                ->chunk_map_node__most_north_western->chunk__here->y 
            || x__chunk > chunk_manager
                ->chunk_map_node__most_south_eastern->chunk__here->x
            || y__chunk < chunk_manager
                ->chunk_map_node__most_south_eastern->chunk__here->y) {
        debug_error("chunk index out of bounds: (%d, %d, %d)",
                x__chunk, y__chunk, z__chunk);
        debug_info("bounds are: (%d, %d) - (%d, %d)",
            chunk_manager->chunk_map_node__most_north_western->chunk__here->x,
            chunk_manager->chunk_map_node__most_north_western->chunk__here->y, 
            chunk_manager->chunk_map_node__most_south_eastern->chunk__here->x,
            chunk_manager->chunk_map_node__most_south_eastern->chunk__here->y);
        return 0;
    }

    int32_t local_x =
        x__chunk - chunk_manager
        ->chunk_map_node__most_north_western->chunk__here->x;
    int32_t local_y =
        y__chunk - chunk_manager
        ->chunk_map_node__most_south_eastern->chunk__here->y;

    return  local_y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
            + local_x;
}

Chunk* get_chunk_from__chunk_manager(
        Chunk_Manager* chunk_manager, 
        int32_t x__chunk, int32_t y__chunk, 
        int32_t z__chunk) {

    // Invert, TODO: look into why
    y__chunk *= -1;

    int32_t north_west__x = chunk_manager
                ->chunk_map_node__most_north_western->chunk__here->x;
    int32_t north_west__y = chunk_manager
                ->chunk_map_node__most_north_western->chunk__here->y;
    int32_t south_east__x = chunk_manager
                ->chunk_map_node__most_south_eastern->chunk__here->x;
    int32_t south_east__y = chunk_manager
                ->chunk_map_node__most_south_eastern->chunk__here->y;

    if (x__chunk < north_west__x
            || y__chunk > north_west__y
            || x__chunk > south_east__x
            || y__chunk < south_east__y) {
        debug_error("chunk index out of bounds: (%d, %d, %d)",
                x__chunk, y__chunk, z__chunk);
        debug_info("bounds are: (%d, %d) - (%d, %d)",
            chunk_manager->chunk_map_node__most_north_western->chunk__here->x,
            chunk_manager->chunk_map_node__most_north_western->chunk__here->y, 
            chunk_manager->chunk_map_node__most_south_eastern->chunk__here->x,
            chunk_manager->chunk_map_node__most_south_eastern->chunk__here->y);
        return 0;
    }

    Chunk_Manager__Chunk_Map_Node *node =
        chunk_manager->chunk_map_node__most_north_western;
    for (int32_t x = north_west__x; x < x__chunk; x++) {
        node = node->chunk_map_node__east;
    }
    for (int32_t y = north_west__y; y > y__chunk; y--) {
        node = node->chunk_map_node__south;
    }

    return node->chunk__here;

    // return &chunk_manager->chunks[
    //     get_chunk_index_at__xyz_from__chunk_manager(
    //             chunk_manager,
    //             x__chunk, 
    //             y__chunk,
    //             z__chunk)
    // ];
}

void move_chunk_manager__chunks_north(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_params) {
    int32_t x__old_most_north_western_chunk =
        chunk_manager->chunk_map_node__most_north_western
            ->chunk__here->x;
    int32_t y__new_most_north_western_chunk =
        chunk_manager->chunk_map_node__most_north_western
            ->chunk__here->y + 1;
    chunk_manager->chunk_map_node__most_north_western =
        chunk_manager->chunk_map_node__most_north_western->chunk_map_node__north;
    chunk_manager->chunk_map_node__most_north_eastern =
        chunk_manager->chunk_map_node__most_north_eastern->chunk_map_node__north;
    chunk_manager->chunk_map_node__most_south_western =
        chunk_manager->chunk_map_node__most_south_western->chunk_map_node__north;
    chunk_manager->chunk_map_node__most_south_eastern =
        chunk_manager->chunk_map_node__most_south_eastern->chunk_map_node__north;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->chunk_map_node__most_north_western;

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
        chunk_manager->chunk_map_node__most_north_eastern
            ->chunk__here->x + 1;
    int32_t y__old_most_south_eastern_chunk =
        chunk_manager->chunk_map_node__most_south_eastern
            ->chunk__here->y;

    chunk_manager->chunk_map_node__most_north_western =
        chunk_manager->chunk_map_node__most_north_western->chunk_map_node__east;
    chunk_manager->chunk_map_node__most_north_eastern =
        chunk_manager->chunk_map_node__most_north_eastern->chunk_map_node__east;
    chunk_manager->chunk_map_node__most_south_western =
        chunk_manager->chunk_map_node__most_south_western->chunk_map_node__east;
    chunk_manager->chunk_map_node__most_south_eastern =
        chunk_manager->chunk_map_node__most_south_eastern->chunk_map_node__east;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->chunk_map_node__most_south_eastern;

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
        chunk_manager->chunk_map_node__most_south_western
            ->chunk__here->x;
    int32_t y__new_most_south_western_chunk =
        chunk_manager->chunk_map_node__most_south_western
            ->chunk__here->y - 1;
    chunk_manager->chunk_map_node__most_north_western =
        chunk_manager->chunk_map_node__most_north_western->chunk_map_node__south;
    chunk_manager->chunk_map_node__most_north_eastern =
        chunk_manager->chunk_map_node__most_north_eastern->chunk_map_node__south;
    chunk_manager->chunk_map_node__most_south_western =
        chunk_manager->chunk_map_node__most_south_western->chunk_map_node__south;
    chunk_manager->chunk_map_node__most_south_eastern =
        chunk_manager->chunk_map_node__most_south_eastern->chunk_map_node__south;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->chunk_map_node__most_south_western;

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
        chunk_manager->chunk_map_node__most_north_western
            ->chunk__here->x - 1;
    int32_t y__old_most_south_western_chunk =
        chunk_manager->chunk_map_node__most_south_western
            ->chunk__here->y;

    chunk_manager->chunk_map_node__most_north_western =
        chunk_manager->chunk_map_node__most_north_western->chunk_map_node__west;
    chunk_manager->chunk_map_node__most_north_eastern =
        chunk_manager->chunk_map_node__most_north_eastern->chunk_map_node__west;
    chunk_manager->chunk_map_node__most_south_western =
        chunk_manager->chunk_map_node__most_south_western->chunk_map_node__west;
    chunk_manager->chunk_map_node__most_south_eastern =
        chunk_manager->chunk_map_node__most_south_eastern->chunk_map_node__west;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->chunk_map_node__most_south_western;

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

bool poll_chunk_manager_for__tile_collision(
        Chunk_Manager *chunk_manager, 
        Entity *entity) {
    if (entity->hitbox.x__velocity == 0
            && entity->hitbox.y__velocity == 0) {
        return true;
    }

    Hitbox_Point aa, bb;
    get_points_aabb_from__hitbox(
            &entity->hitbox, &aa, &bb);

    Tile *tile;
    //TODO: magic num
    int32_t global_positions[8] = {
        aa.x, aa.y,
        bb.x, aa.y,
        aa.x, bb.y,
        bb.x, bb.y
    };
    int32_t local_positions[8] = {
        (aa.x >> 3) & ((1 << 3) - 1), (aa.y >> 3) & ((1 << 3) - 1),
        (bb.x >> 3) & ((1 << 3) - 1), (aa.y >> 3) & ((1 << 3) - 1),
        (aa.x >> 3) & ((1 << 3) - 1), (bb.y >> 3) & ((1 << 3) - 1),
        (bb.x >> 3) & ((1 << 3) - 1), (bb.y >> 3) & ((1 << 3) - 1)
    };

    for (uint32_t index=0;index<8;index+=2) {
        int32_t x__chunk =
            global_positions[index] >> 6; //entity->hitbox.x__chunk;
        int32_t y__chunk =
            global_positions[index+1] >> 6; //entity->hitbox.y__chunk;

        Chunk *chunk =
            get_chunk_from__chunk_manager(
                    chunk_manager,
                    x__chunk,
                    y__chunk,
                    0);

        //TODO: this error occurs regularly when entity off screen 
        //need to fix.
        if (!chunk) {
            debug_warning("entity out of tile collision bounds.");
            debug_info("access attempt: %d, %d",
                    x__chunk, y__chunk);
            return true;
        }

        Tile *tile =
            get_tile_from__chunk(
                    chunk,
                    local_positions[index],
                    local_positions[index+1],
                    0);

        if (is_tile__unpassable(tile)) {
            if (entity->tile_collision_handler) {
                entity->tile_collision_handler(
                        entity,
                        tile);
            }
            return true;
        }
    }

    return true;
}
