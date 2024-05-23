#include <defines.h>
#include <world/chunk.h>
#include <debug/debug.h>

#include <world/tile.h>
#include <collisions/hitbox_aabb.h>

void init_chunk_manager(
        Chunk_Manager* chunk_manager,
        World_Parameters *world_parameters) {
    chunk_manager->x__center_chunk__signed_index_i32 =
        chunk_manager->y__center_chunk__signed_index_i32 = 0;
    for (Signed_Index__i32 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Signed_Index__i32 x=0; x <
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

            world_parameters->f_chunk_generator(world_parameters, chunk__here);

            chunk_map_node->chunk__here = chunk__here;

            Index_u32 x__east, x__west, y__north, y__south;

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
            chunk_map_node->north__chunk_map_node =
                &chunk_manager->chunk_map[
                y__north * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x
                ];

            // link east
            chunk_map_node->east__chunk_map_node =
                &chunk_manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                + x__east
                ];

            // link south
            chunk_map_node->south__chunk_map_node =
                &chunk_manager->chunk_map[
                y__south * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x 
                ];

            // link west
            chunk_map_node->west__chunk_map_node =
                &chunk_manager->chunk_map[
                y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                + x__west
                ];
        }
    }

    chunk_manager->most_north_western__chunk_map_node =
        &chunk_manager->chunk_map[0];

    chunk_manager->most_north_eastern__chunk_map_node =
        &chunk_manager->chunk_map[
        GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1];

    chunk_manager->most_south_western__chunk_map_node =
        &chunk_manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW];

    chunk_manager->most_south_eastern__chunk_map_node =
        &chunk_manager->chunk_map[
        (GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS - 1
        ];
}

uint32_t get_chunk_index_at__xyz_from__chunk_manager(
        Chunk_Manager *chunk_manager,
        Signed_Index__i32 x__chunk, 
        Signed_Index__i32 y__chunk,
        Signed_Index__i32 z__chunk) {
    // TODO: extend to use z

    if (x__chunk < chunk_manager
            ->most_north_western__chunk_map_node
                ->chunk__here->x__signed_index_i32
            || y__chunk > chunk_manager
                ->most_north_western__chunk_map_node
                    ->chunk__here->y__signed_index_i32
            || x__chunk > chunk_manager
                ->most_south_eastern__chunk_map_node
                    ->chunk__here->x__signed_index_i32
            || y__chunk < chunk_manager
                ->most_south_eastern__chunk_map_node
                    ->chunk__here->y__signed_index_i32) {
        debug_error("chunk index out of bounds: (%d, %d, %d)",
                x__chunk, y__chunk, z__chunk);
        debug_info("bounds are: (%d, %d) - (%d, %d)",
            chunk_manager->most_north_western__chunk_map_node
                ->chunk__here->x__signed_index_i32,
            chunk_manager->most_north_western__chunk_map_node
                ->chunk__here->y__signed_index_i32, 
            chunk_manager->most_south_eastern__chunk_map_node
                ->chunk__here->x__signed_index_i32,
            chunk_manager->most_south_eastern__chunk_map_node
                ->chunk__here->y__signed_index_i32);
        return 0;
    }

    Signed_Index__i32 local_x =
        x__chunk - chunk_manager
        ->most_north_western__chunk_map_node
            ->chunk__here->x__signed_index_i32;
    Signed_Index__i32 local_y =
        y__chunk - chunk_manager
        ->most_south_eastern__chunk_map_node
            ->chunk__here->y__signed_index_i32;

    return  local_y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
            + local_x;
}

Chunk* get_chunk_from__chunk_manager(
        Chunk_Manager* chunk_manager, 
        Signed_Index__i32 x__chunk, 
        Signed_Index__i32 y__chunk, 
        Signed_Index__i32 z__chunk) {

    // Invert, TODO: look into why
    y__chunk *= -1;

    Signed_Index__i32 north_west__x = chunk_manager
                ->most_north_western__chunk_map_node
                    ->chunk__here->x__signed_index_i32;
    Signed_Index__i32 north_west__y = chunk_manager
                ->most_north_western__chunk_map_node
                    ->chunk__here->y__signed_index_i32;
    Signed_Index__i32 south_east__x = chunk_manager
                ->most_south_eastern__chunk_map_node
                    ->chunk__here->x__signed_index_i32;
    Signed_Index__i32 south_east__y = chunk_manager
                ->most_south_eastern__chunk_map_node
                    ->chunk__here->y__signed_index_i32;

    if (x__chunk < north_west__x
            || y__chunk > north_west__y
            || x__chunk > south_east__x
            || y__chunk < south_east__y) {
        debug_error("chunk index out of bounds: (%d, %d, %d)",
                x__chunk, y__chunk, z__chunk);
        debug_info("bounds are: (%d, %d) - (%d, %d)",
            chunk_manager->most_north_western__chunk_map_node
                ->chunk__here->x__signed_index_i32,
            chunk_manager->most_north_western__chunk_map_node
                ->chunk__here->y__signed_index_i32, 
            chunk_manager->most_south_eastern__chunk_map_node
                ->chunk__here->x__signed_index_i32,
            chunk_manager->most_south_eastern__chunk_map_node
                ->chunk__here->y__signed_index_i32);
        return 0;
    }

    Chunk_Manager__Chunk_Map_Node *node =
        chunk_manager->most_north_western__chunk_map_node;
    for (Signed_Index__i32 x = north_west__x; x < x__chunk; x++) {
        node = node->east__chunk_map_node;
    }
    for (Signed_Index__i32 y = north_west__y; y > y__chunk; y--) {
        node = node->south__chunk_map_node;
    }

    return node->chunk__here;
}

void move_chunk_manager__chunks_north(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_parameters) {
    Signed_Index__i32 x__old_most_north_western_chunk =
        chunk_manager->most_north_western__chunk_map_node
            ->chunk__here->x__signed_index_i32;
    Signed_Index__i32 y__new_most_north_western_chunk =
        chunk_manager->most_north_western__chunk_map_node
            ->chunk__here->y__signed_index_i32 + 1;
    chunk_manager->most_north_western__chunk_map_node =
        chunk_manager->most_north_western__chunk_map_node
            ->north__chunk_map_node;
    chunk_manager->most_north_eastern__chunk_map_node =
        chunk_manager->most_north_eastern__chunk_map_node
            ->north__chunk_map_node;
    chunk_manager->most_south_western__chunk_map_node =
        chunk_manager->most_south_western__chunk_map_node
            ->north__chunk_map_node;
    chunk_manager->most_south_eastern__chunk_map_node =
        chunk_manager->most_south_eastern__chunk_map_node
            ->north__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->most_north_western__chunk_map_node;

    for (Quantity__u32 step = 0; 
            step < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x__signed_index_i32 !=
                (x__old_most_north_western_chunk + step)
                || chunk__here->y__signed_index_i32 
                != y__new_most_north_western_chunk) {

            chunk__here->x__signed_index_i32 =
                x__old_most_north_western_chunk + step;
            chunk__here->y__signed_index_i32 =
                y__new_most_north_western_chunk;

            world_parameters->f_chunk_generator(
                    world_parameters,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->east__chunk_map_node;
    }
}

void move_chunk_manager__chunks_east(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_parameters) {
    int32_t x__new_most_north_eastern_chunk =
        chunk_manager->most_north_eastern__chunk_map_node
            ->chunk__here->x__signed_index_i32 + 1;
    int32_t y__old_most_south_eastern_chunk =
        chunk_manager->most_south_eastern__chunk_map_node
            ->chunk__here->y__signed_index_i32;

    chunk_manager->most_north_western__chunk_map_node =
        chunk_manager->most_north_western__chunk_map_node
            ->east__chunk_map_node;
    chunk_manager->most_north_eastern__chunk_map_node =
        chunk_manager->most_north_eastern__chunk_map_node
            ->east__chunk_map_node;
    chunk_manager->most_south_western__chunk_map_node =
        chunk_manager->most_south_western__chunk_map_node
            ->east__chunk_map_node;
    chunk_manager->most_south_eastern__chunk_map_node =
        chunk_manager->most_south_eastern__chunk_map_node
            ->east__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->most_south_eastern__chunk_map_node;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x__signed_index_i32 !=
                x__new_most_north_eastern_chunk
                || (chunk__here->y__signed_index_i32 != 
                    y__old_most_south_eastern_chunk + step)) {

            chunk__here->x__signed_index_i32 =
                x__new_most_north_eastern_chunk;
            chunk__here->y__signed_index_i32 =
                y__old_most_south_eastern_chunk + step;

            world_parameters->f_chunk_generator(
                    world_parameters,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->north__chunk_map_node;
    }
}

void move_chunk_manager__chunks_south(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_parameters) {
    int32_t x__old_most_south_western_chunk=
        chunk_manager->most_south_western__chunk_map_node
            ->chunk__here->x__signed_index_i32;
    int32_t y__new_most_south_western_chunk=
        chunk_manager->most_south_western__chunk_map_node
            ->chunk__here->y__signed_index_i32 - 1;
    chunk_manager->most_north_western__chunk_map_node =
        chunk_manager->most_north_western__chunk_map_node
            ->south__chunk_map_node;
    chunk_manager->most_north_eastern__chunk_map_node =
        chunk_manager->most_north_eastern__chunk_map_node
            ->south__chunk_map_node;
    chunk_manager->most_south_western__chunk_map_node =
        chunk_manager->most_south_western__chunk_map_node
            ->south__chunk_map_node;
    chunk_manager->most_south_eastern__chunk_map_node =
        chunk_manager->most_south_eastern__chunk_map_node
            ->south__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->most_south_western__chunk_map_node;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x__signed_index_i32 !=
                (x__old_most_south_western_chunk + step)
                || chunk__here->y__signed_index_i32 
                != y__new_most_south_western_chunk) {

            chunk__here->x__signed_index_i32 =
                x__old_most_south_western_chunk + step;
            chunk__here->y__signed_index_i32 =
                y__new_most_south_western_chunk;

            world_parameters->f_chunk_generator(
                    world_parameters,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->east__chunk_map_node;
    }
}

void move_chunk_manager__chunks_west(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_parameters) {
    int32_t x__new_most_north_western_chunk =
        chunk_manager->most_north_western__chunk_map_node
            ->chunk__here->x__signed_index_i32 - 1;
    int32_t y__old_most_south_western_chunk =
        chunk_manager->most_south_western__chunk_map_node
            ->chunk__here->y__signed_index_i32;

    chunk_manager->most_north_western__chunk_map_node =
        chunk_manager->most_north_western__chunk_map_node
            ->west__chunk_map_node;
    chunk_manager->most_north_eastern__chunk_map_node =
        chunk_manager->most_north_eastern__chunk_map_node
            ->west__chunk_map_node;
    chunk_manager->most_south_western__chunk_map_node =
        chunk_manager->most_south_western__chunk_map_node
            ->west__chunk_map_node;
    chunk_manager->most_south_eastern__chunk_map_node =
        chunk_manager->most_south_eastern__chunk_map_node
            ->west__chunk_map_node;

    Chunk_Manager__Chunk_Map_Node *current__chunk_map_node =
        chunk_manager->most_south_western__chunk_map_node;

    for (uint32_t step = 0; 
            step < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            step++) {
        Chunk *chunk__here =
            current__chunk_map_node->chunk__here;
        if (chunk__here->x__signed_index_i32 !=
                x__new_most_north_western_chunk
                || (chunk__here->y__signed_index_i32 != 
                    y__old_most_south_western_chunk + step)) {

            chunk__here->x__signed_index_i32 =
                x__new_most_north_western_chunk;
            chunk__here->y__signed_index_i32 =
                y__old_most_south_western_chunk + step;

            world_parameters->f_chunk_generator(
                    world_parameters,
                    chunk__here);
        }

        current__chunk_map_node = 
            current__chunk_map_node->north__chunk_map_node;
    }
}

void move_chunk_manager(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_parameters,
        Direction direction,
        Quantity__u32 steps) {
    for (Quantity__u32 step=0; step < steps; step++) {
        if (direction & DIRECTION__NORTH) {
            move_chunk_manager__chunks_north(
                    chunk_manager, 
                    world_parameters);
        }
        if (direction & DIRECTION__EAST) {
            move_chunk_manager__chunks_east(
                    chunk_manager, 
                    world_parameters);
        }
        if (direction & DIRECTION__SOUTH) {
            move_chunk_manager__chunks_south(
                    chunk_manager, 
                    world_parameters);
        }
        if (direction & DIRECTION__WEST) {
            move_chunk_manager__chunks_west(
                    chunk_manager, 
                    world_parameters);
        }
    }
}

bool poll_chunk_manager_for__chunk_movement(
        Chunk_Manager *chunk_manager,
        World_Parameters *world_parameters,
        Signed_Index__i32 x__chunk, 
        Signed_Index__i32 y__chunk,
        Signed_Index__i32 z__chunk) {

    Direction__u8 direction__move_chunks = DIRECTION__NONE;

    if (x__chunk != chunk_manager->x__center_chunk__signed_index_i32 
        || y__chunk != chunk_manager->y__center_chunk__signed_index_i32) {
        if (chunk_manager->x__center_chunk__signed_index_i32 < x__chunk) {
            direction__move_chunks |=
                DIRECTION__EAST;
        } else if (chunk_manager->x__center_chunk__signed_index_i32 
                > x__chunk) {
            direction__move_chunks |=
                DIRECTION__WEST;
        }
        if (chunk_manager->y__center_chunk__signed_index_i32 > y__chunk) {
            direction__move_chunks |=
                DIRECTION__NORTH;
        } else if (chunk_manager->y__center_chunk__signed_index_i32 
                < y__chunk) {
            direction__move_chunks |=
                DIRECTION__SOUTH;
        }
        chunk_manager->x__center_chunk__signed_index_i32 = x__chunk;
        chunk_manager->y__center_chunk__signed_index_i32 = y__chunk;
    }

    if(direction__move_chunks != DIRECTION__NONE) {
        move_chunk_manager(
                chunk_manager, 
                world_parameters, 
                direction__move_chunks,
                1);
        return true;
    }

    return false;
}

bool poll_chunk_manager_for__tile_collision(
        Chunk_Manager *chunk_manager, 
        Entity *entity) {
    if (entity->hitbox.x__velocity__i32F4 == 0
            && entity->hitbox.y__velocity__i32F4 == 0) {
        return true;
    }

    Vector__3i32F4 aa, bb;
    get_points_aabb_from__hitbox(
            &entity->hitbox, &aa, &bb);

    Tile *tile;
    //TODO: magic num
    i32F4 global_positions[8] = {
        aa.x__i32F4, aa.y__i32F4,
        bb.x__i32F4, aa.y__i32F4,
        aa.x__i32F4, bb.y__i32F4,
        bb.x__i32F4, bb.y__i32F4
    };
    Signed_Index__i32 local_positions[8] = {
        (aa.x__i32F4 >> 3) & ((1 << 3) - 1), 
        (aa.y__i32F4 >> 3) & ((1 << 3) - 1),
        (bb.x__i32F4 >> 3) & ((1 << 3) - 1), 
        (aa.y__i32F4 >> 3) & ((1 << 3) - 1),
        (aa.x__i32F4 >> 3) & ((1 << 3) - 1), 
        (bb.y__i32F4 >> 3) & ((1 << 3) - 1),
        (bb.x__i32F4 >> 3) & ((1 << 3) - 1), 
        (bb.y__i32F4 >> 3) & ((1 << 3) - 1)
    };

    for (Index_u32 index=0;index<8;index+=2) {
        Signed_Index__i32 x__chunk =
            global_positions[index] >> 6; //entity->hitbox.x__chunk;
        Signed_Index__i32 y__chunk =
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
