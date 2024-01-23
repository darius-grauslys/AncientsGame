#include <collisions/collision_manager.h>
#include <debug/debug.h>
#include <collisions/hitbox_aabb.h>

///
/// (0,7)    (1.5,7)                (4.5,7)
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: :: (7,7) 
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: :: 
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  .
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  . 
/// ------------+--------------||-------------+------------
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: ::
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: ::
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  .
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  .
/// ___________________________##__________________________ (7,3.5)
/// ---------------------------##--------------------------
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: :: 
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: :: 
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  . 
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  . 
/// ------------+--------------||-------------+------------
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: ::
///  .  . :: :: |  .  . :: ::  ||  .  . :: :: |  .  . :: :: (7,1)
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  .
/// :: ::  .  . | :: ::  .  .  || :: ::  .  . | :: ::  .  . 
/// (0,0)                    (3.5,0)                  (7,0)
///
/// This is a representation of
/// the Collision_Manager data-structure in memory.
///
/// (0,0) is collision_nodes[0]
///

///
/// This is to only be called during
/// initalization, since layer_one
/// (x/y)__center_chunk is
/// CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2.
///
/// Most north west collision node is:
///     x__chunk == 0
///     y__chunk == 0
///
/// In otherwords, we don't need to do
/// any modulus to obtain a bounded index
/// of [0, CHUNK_MANAGER__QUANTITY_OF_CHUNKS - 1]
///
static uint32_t inline get_collision_node_index_during__initialization(
    int32_t x__chunk, int32_t y__chunk) {
    return y__chunk
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + x__chunk
        ;
}

void update_collision_manager__layer_three(
        Collision_Manager__Layer_Three *layer_three, 
        Collision_Manager__Layer_Two *layer_two,
        Direction quadrant_direction) {
    
    ///
    /// Magic numbers are justified here.
    /// We offset out (x/y)__center_chunk
    /// by the quantity of chunks in a
    /// chunk_manager row divided by
    /// 2^(layer)
    /// where collision_manager is layer_one
    ///
    /// So since this is layer_three, its
    /// divide by 8.
    ///
    /// This value is ONLY used here, so
    /// 8 is not put behind a macro.
    ///

    switch (quadrant_direction) {
        default:
            debug_abort("Failed to init collision_manager \
bad quadrant_direction layer_three.");
            return;
        case DIRECTION__NORTH_EAST:
            layer_three->x__center_chunk =
                layer_two->x__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            break;
        case DIRECTION__NORTH_WEST:
            layer_three->x__center_chunk =
                layer_two->x__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            break;
        case DIRECTION__SOUTH_EAST:
            layer_three->x__center_chunk =
                layer_two->x__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            break;
        case DIRECTION__SOUTH_WEST:
            layer_three->x__center_chunk =
                layer_two->x__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 8;
            break;
    }
}

void update_collision_manager__layer_two(
        Collision_Manager__Layer_Two *layer_two, 
        Collision_Manager *collision_manager,
        Direction quadrant_direction) {
    switch (quadrant_direction) {
        default:
            debug_abort("Failed to update collision_manager \
bad quadrant_direction layer_two.");
            return;
        case DIRECTION__NORTH_EAST:
            layer_two->x__center_chunk =
                collision_manager->x__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            break;
        case DIRECTION__NORTH_WEST:
            layer_two->x__center_chunk =
                collision_manager->x__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            break;
        case DIRECTION__SOUTH_EAST:
            layer_two->x__center_chunk =
                collision_manager->x__center_chunk
                + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            break;
        case DIRECTION__SOUTH_WEST:
            layer_two->x__center_chunk =
                collision_manager->x__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 4;
            break;
    }

    // debug_info("layer2: %d, %d",
    //         layer_two->x__center_chunk,
    //         layer_two->y__center_chunk);

    update_collision_manager__layer_three(
            &layer_two->layer_three__top_left, 
            layer_two, 
            DIRECTION__NORTH_WEST);
    update_collision_manager__layer_three(
            &layer_two->layer_three__top_right, 
            layer_two, 
            DIRECTION__NORTH_EAST);
    update_collision_manager__layer_three(
            &layer_two->layer_three__bottom_left, 
            layer_two, 
            DIRECTION__SOUTH_EAST);
    update_collision_manager__layer_three(
            &layer_two->layer_three__bottom_right, 
            layer_two, 
            DIRECTION__SOUTH_WEST);
}

void init_collision_manager__layer_three(
        Collision_Manager__Layer_Three *layer_three,
        Collision_Manager *collision_manager,
        Collision_Manager__Layer_Two *layer_two,
        Direction quadrant_direction) {

    layer_three->collision_node__top_right =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk + 1, 
                    layer_three->y__center_chunk  + 1)
        ];
    layer_three->collision_node__top_left =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk - 1, 
                    layer_three->y__center_chunk  + 1)
        ];
    layer_three->collision_node__bottom_right =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk + 1, 
                    layer_three->y__center_chunk  - 1)
        ];
    layer_three->collision_node__bottom_left =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk - 1, 
                    layer_three->y__center_chunk  - 1)
        ];
}

void init_collision_manager__layer_two(
        Collision_Manager__Layer_Two *layer_two,
        Collision_Manager *collision_manager,
        Direction quadrant_direction) {

    update_collision_manager__layer_two(
            layer_two, 
            collision_manager, 
            quadrant_direction);
    
    init_collision_manager__layer_three(
            &layer_two->layer_three__top_left, 
            collision_manager, 
            layer_two, 
            DIRECTION__NORTH_WEST);
    init_collision_manager__layer_three(
            &layer_two->layer_three__top_right, 
            collision_manager, 
            layer_two, 
            DIRECTION__NORTH_EAST);
    init_collision_manager__layer_three(
            &layer_two->layer_three__bottom_left, 
            collision_manager, 
            layer_two, 
            DIRECTION__SOUTH_EAST);
    init_collision_manager__layer_three(
            &layer_two->layer_three__bottom_right, 
            collision_manager, 
            layer_two, 
            DIRECTION__SOUTH_WEST);
}

void init_collision_manager(
        Collision_Manager *collision_manager) {
    collision_manager->x__center_chunk =
        collision_manager->y__center_chunk = 
        CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2;

    for (int32_t y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (int32_t x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Collision_Manager__Collision_Node *collision_node=
                &collision_manager->collision_nodes[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                        + x
                ];

            collision_node->legal_directions = DIRECTION__NONE;

            // x==0 -> x==0
            // link west
            if (x == 0) {
                // wrap around.
                collision_node->collision_node__west = 
                    &collision_manager->collision_nodes[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                    + (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1)
                    ];
            } else {
                collision_node->collision_node__west =
                    &collision_manager->collision_nodes[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                    + x - 1
                    ];
                collision_node->legal_directions |=
                    DIRECTION__WEST;
            }
            // link east
            if (x == CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1) {
                collision_node->collision_node__east =
                    &collision_manager->collision_nodes[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                    ];
            } else {
                collision_node->collision_node__east =
                    &collision_manager->collision_nodes[
                    y * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                    + x + 1
                    ];
                collision_node->legal_directions |=
                    DIRECTION__EAST;
            }

            // y==0 -> y==7
            // link north
            if (y == 0) {
                collision_node->collision_node__north =
                    &collision_manager->collision_nodes[
                    (CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW - 1) 
                    * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                    + x
                    ];
            } else {
                collision_node->collision_node__north =
                    &collision_manager->collision_nodes[
                    (y - 1) * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW 
                    + x
                    ];
                collision_node->legal_directions |=
                    DIRECTION__NORTH;
            }
            // link south
            if (y == CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - 1) {
                collision_node->collision_node__south =
                    &collision_manager->collision_nodes[x];
            } else {
                collision_node->collision_node__south =
                    &collision_manager->collision_nodes[
                    (y + 1) * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
                    + x 
                    ];
                collision_node->legal_directions |=
                    DIRECTION__SOUTH;
            }
        }
    }

    init_collision_manager__layer_two(
            &collision_manager->layer_two__top_left, 
            collision_manager, 
            DIRECTION__NORTH_WEST);
    init_collision_manager__layer_two(
            &collision_manager->layer_two__top_right, 
            collision_manager, 
            DIRECTION__NORTH_EAST);
    init_collision_manager__layer_two(
            &collision_manager->layer_two__bottom_left, 
            collision_manager, 
            DIRECTION__SOUTH_EAST);
    init_collision_manager__layer_two(
            &collision_manager->layer_two__bottom_right, 
            collision_manager, 
            DIRECTION__SOUTH_WEST);

    collision_manager->most_north_western__node =
        &collision_manager->collision_nodes[0];
}

Collision_Manager__Collision_Node 
*get_collision_node_for__this_position(
        Collision_Manager *collision_manager,
        int32_t x__chunk,
        int32_t y__chunk
        ) {
    Collision_Manager__Layer_Two *layer_two;

    if (x__chunk <
            collision_manager->x__center_chunk) {
        if (y__chunk <
                collision_manager->y__center_chunk) {
            layer_two =
                &collision_manager->layer_two__bottom_left;
        } else {
            layer_two =
                &collision_manager->layer_two__top_left;
        }
    } else {
        if (y__chunk <
                collision_manager->y__center_chunk) {
            layer_two =
                &collision_manager->layer_two__bottom_right;
        } else {
            layer_two =
                &collision_manager->layer_two__top_right;
        }
    }

    Collision_Manager__Layer_Three *layer_three;

    if (x__chunk <
            layer_two->x__center_chunk) {
        if (y__chunk <
                layer_two->y__center_chunk) {
            layer_three =
                &layer_two->layer_three__bottom_left;
        } else {
            layer_three =
                &layer_two->layer_three__top_left;
        }
    } else {
        if (y__chunk <
                layer_two->y__center_chunk) {
            layer_three =
                &layer_two->layer_three__bottom_right;
        } else {
            layer_three =
                &layer_two->layer_three__top_right;
        }
    }

    Collision_Manager__Collision_Node *collision_node;

    if (x__chunk <
            layer_three->x__center_chunk) {
        if (y__chunk <
                layer_three->y__center_chunk) {
            collision_node =
                layer_three->collision_node__bottom_left;
        } else {
            collision_node =
                layer_three->collision_node__top_left;
        }
    } else {
        if (y__chunk <
                layer_three->y__center_chunk) {
            collision_node =
                layer_three->collision_node__bottom_right;
        } else {
            collision_node =
                layer_three->collision_node__top_right;
        }
    }

    return collision_node;
}

bool is_this_entity_colliding_into__this_entity(
        Entity *entity_collision_source,
        Entity *entity_collided) {
    return is_hitboxes__overlapping(
            &entity_collision_source->hitbox, 
            &entity_collided->hitbox);
}

void check_collision_node_for__collisions(
        Collision_Manager__Collision_Node *collision_node,
        Entity *entity) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        // All collisions checked.
        if (!collision_node->entity_ptrs[i]) {
            return;
        }

        if (collision_node->entity_ptrs[i] ==
                entity) {
            // Do not collide with yourself!
            continue;
        }

        if (is_this_entity_colliding_into__this_entity(
                    entity,
                    collision_node->entity_ptrs[i])) {
            if (entity->collision_handler) {
                entity->collision_handler(entity,
                        collision_node->entity_ptrs[i]);
            }
        }
    }
}

void poll_collision_mannager(
        Collision_Manager *collision_manager,
        Entity *entity) {
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                entity->hitbox.x__chunk,
                entity->hitbox.y__chunk);

    check_collision_node_for__collisions(
            collision_node, 
            entity);

    // north
    if (collision_node->legal_directions & DIRECTION__NORTH) {
        check_collision_node_for__collisions(
                collision_node->collision_node__north, 
                entity);
        // north east
        if (collision_node->legal_directions & DIRECTION__EAST) {
            check_collision_node_for__collisions(
                    collision_node->collision_node__north
                        ->collision_node__east, 
                    entity);
        }
        // north west
        if (collision_node->legal_directions & DIRECTION__WEST) {
            check_collision_node_for__collisions(
                    collision_node->collision_node__north
                        ->collision_node__west, 
                    entity);
        }
    }
    // south
    if (collision_node->legal_directions & DIRECTION__SOUTH) {
        check_collision_node_for__collisions(
                collision_node->collision_node__south, 
                entity);
        // south east
        if (collision_node->legal_directions & DIRECTION__EAST) {
            check_collision_node_for__collisions(
                    collision_node->collision_node__south
                        ->collision_node__east, 
                    entity);
        }
        // south west
        if (collision_node->legal_directions & DIRECTION__WEST) {
            check_collision_node_for__collisions(
                    collision_node->collision_node__south
                        ->collision_node__west, 
                    entity);
        }
    }
    // east
    if (collision_node->legal_directions & DIRECTION__EAST) {
        check_collision_node_for__collisions(
                collision_node->collision_node__east, 
                entity);
    }
    // west
    if (collision_node->legal_directions & DIRECTION__WEST) {
        check_collision_node_for__collisions(
                collision_node->collision_node__west, 
                entity);
    }
}

void remove_entity_from__collision_node(
        Collision_Manager__Collision_Node *collision_node,
        Entity *entity) {

    if (!collision_node->entity_ptrs[0]) {
        // Did you modify the entity's x__chunk, y__chunk
        // BEFORE removing the entity from it's old
        // collision node?
        //
        // Whenever you modify the entity's x__chunk, y__chunk
        // you must FIRST remove it from it's current collision node.
        // Reminder: Projectiles can check for collisions, but they
        // cannot themselves be collided. In otherwords, there
        // is no need to remove projectiles from collision nodes.
        // Since they will never reside in a collision node.
        debug_error("Tried to remove entity from an \
empty collision node.");
        return;
    }

    Entity **removed_entity_ptr_slot = 0;
    Entity **last_entity_ptr_slot = 0;
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        if (collision_node->entity_ptrs[i] == entity) {
            removed_entity_ptr_slot =
                &collision_node->entity_ptrs[i];
            continue;
        }
        if (!collision_node->entity_ptrs[i]) {
            last_entity_ptr_slot =
                &collision_node->entity_ptrs[i-1];
            break;
        }
        if (ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE
                == i + 1) {
            last_entity_ptr_slot =
                &collision_node->entity_ptrs[i];
            break;
        }
    }

    if (!removed_entity_ptr_slot) {
        // Did you modify the entity's x__chunk, y__chunk
        // BEFORE removing the entity from it's old
        // collision node?
        //
        // Whenever you modify the entity's x__chunk, y__chunk
        // you must FIRST remove it from it's current collision node.
        // Reminder: Projectiles can check for collisions, but they
        // cannot themselves be collided. In otherwords, there
        // is no need to remove projectiles from collision nodes.
        // Since they will never reside in a collision node.
        debug_error("Could not find entity inside of it's \
collision node.");
        return;
    }
    // Keep the entity array tightly packed.
    // Order doesn't matter.
    *removed_entity_ptr_slot =
        *last_entity_ptr_slot;
    *last_entity_ptr_slot = 0;
}

///
/// This is called because the node "fell off" the map.
///
void unload_all_entities_from__collision_node(
        Collision_Manager__Collision_Node *collision_node,
        Game *game) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        Entity *entity =
            collision_node->entity_ptrs[i];
        if (!entity) {
            if (entity->dispose_handler) {
                entity->dispose_handler(entity, game);
            }
            // Don't do this, since dispose_handler
            // will call release_entity(...);
            // collision_node->entity_ptrs[i] = 0;
        }
    }
}

void add_entity_to__collision_node(
        Collision_Manager__Collision_Node *collision_node,
        Entity *entity) {
    // we should always have enough room.

    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        if (!collision_node->entity_ptrs[i]) {
            collision_node->entity_ptrs[i] =
                entity;
            return;
        }
    }

    // this should be impossible.
    // if this happens, your platform_defines
    // PLATFORM__ENTITIES is incorrect.
    //
    // Make sure ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE
    // is equal to:
    //      ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS
    //      + ENTITY_MAXIMUM_QUANTITY_OF__NPCS
    //
    // ALSO: Do not add projectiles to collision nodes!
    // Projectiles can check if they collide into an
    // entity, but entities cannot check if they collide
    // into projectiles!
    debug_abort("Failed to add entity to collision node.");
}

void add_entity_to__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity) {
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                entity->hitbox.x__chunk,
                entity->hitbox.y__chunk);

    // debug_info("added entity to node: %d, %d",
    //         collision_node->x__chunk,
    //         collision_node->y__chunk);
    add_entity_to__collision_node(
            collision_node, entity);
}

void remove_entity_from__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity,
        int32_t old_x__chunk,
        int32_t old_y__chunk) {
    // debug_info("old_chunk %d, %d vs new %d, %d",
    //         old_x__chunk,
    //         old_y__chunk,
    //         entity->hitbox.x__chunk,
    //         entity->hitbox.y__chunk);
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                old_x__chunk,
                old_y__chunk);

    // debug_info("remove entity to node: %d, %d",
    //         collision_node->x__chunk,
    //         collision_node->y__chunk);
    remove_entity_from__collision_node(
            collision_node, entity);
}

static void inline move_collision_node__north(
        Collision_Manager__Collision_Node **collision_node_ptrptr) {
    *collision_node_ptrptr =
        (*collision_node_ptrptr)->collision_node__north;
}
static void inline move_collision_node__east(
        Collision_Manager__Collision_Node **collision_node_ptrptr) {
    *collision_node_ptrptr =
        (*collision_node_ptrptr)->collision_node__east;
}
static void inline move_collision_node__south(
        Collision_Manager__Collision_Node **collision_node_ptrptr) {
    *collision_node_ptrptr =
        (*collision_node_ptrptr)->collision_node__south;
}
static void inline move_collision_node__west(
        Collision_Manager__Collision_Node **collision_node_ptrptr) {
    *collision_node_ptrptr =
        (*collision_node_ptrptr)->collision_node__west;
}

static void inline move_collision_manager__layer_three_north(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__north(
        &layer_three
            ->collision_node__top_left);
    move_collision_node__north(
        &layer_three
            ->collision_node__top_right);
    move_collision_node__north(
        &layer_three
            ->collision_node__bottom_left);
    move_collision_node__north(
        &layer_three
            ->collision_node__bottom_right);
}

static void inline move_collision_manager__layer_three_east(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__east(
        &layer_three
            ->collision_node__top_left);
    move_collision_node__east(
        &layer_three
            ->collision_node__top_right);
    move_collision_node__east(
        &layer_three
            ->collision_node__bottom_left);
    move_collision_node__east(
        &layer_three
            ->collision_node__bottom_right);
}

static void inline move_collision_manager__layer_three_south(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__south(
        &layer_three
            ->collision_node__top_left);
    move_collision_node__south(
        &layer_three
            ->collision_node__top_right);
    move_collision_node__south(
        &layer_three
            ->collision_node__bottom_left);
    move_collision_node__south(
        &layer_three
            ->collision_node__bottom_right);
}

static void inline move_collision_manager__layer_three_west(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__west(
        &layer_three
            ->collision_node__top_left);
    move_collision_node__west(
        &layer_three
            ->collision_node__top_right);
    move_collision_node__west(
        &layer_three
            ->collision_node__bottom_left);
    move_collision_node__west(
        &layer_three
            ->collision_node__bottom_right);
}

void move_collision_manager__layer_two_north(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_north(
            &layer_two->layer_three__top_left);
    move_collision_manager__layer_three_north(
            &layer_two->layer_three__top_right);
    move_collision_manager__layer_three_north(
            &layer_two->layer_three__bottom_left);
    move_collision_manager__layer_three_north(
            &layer_two->layer_three__bottom_right);
}

void move_collision_manager__layer_two_east(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_east(
            &layer_two->layer_three__top_left);
    move_collision_manager__layer_three_east(
            &layer_two->layer_three__top_right);
    move_collision_manager__layer_three_east(
            &layer_two->layer_three__bottom_left);
    move_collision_manager__layer_three_east(
            &layer_two->layer_three__bottom_right);
}

void move_collision_manager__layer_two_south(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_south(
            &layer_two->layer_three__top_left);
    move_collision_manager__layer_three_south(
            &layer_two->layer_three__top_right);
    move_collision_manager__layer_three_south(
            &layer_two->layer_three__bottom_left);
    move_collision_manager__layer_three_south(
            &layer_two->layer_three__bottom_right);
}

void move_collision_manager__layer_two_west(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_west(
            &layer_two->layer_three__top_left);
    move_collision_manager__layer_three_west(
            &layer_two->layer_three__top_right);
    move_collision_manager__layer_three_west(
            &layer_two->layer_three__bottom_left);
    move_collision_manager__layer_three_west(
            &layer_two->layer_three__bottom_right);
}

void move_collision_manager__nodes(
        Collision_Manager *collision_manager,
        Direction direction) {
    if (direction & DIRECTION__NORTH) {
        move_collision_manager__layer_two_north(
                &collision_manager->layer_two__top_left);
        move_collision_manager__layer_two_north(
                &collision_manager->layer_two__top_right);
        move_collision_manager__layer_two_north(
                &collision_manager->layer_two__bottom_left);
        move_collision_manager__layer_two_north(
                &collision_manager->layer_two__bottom_right);
    } else if (direction & DIRECTION__SOUTH) {
        move_collision_manager__layer_two_south(
                &collision_manager->layer_two__top_left);
        move_collision_manager__layer_two_south(
                &collision_manager->layer_two__top_right);
        move_collision_manager__layer_two_south(
                &collision_manager->layer_two__bottom_left);
        move_collision_manager__layer_two_south(
                &collision_manager->layer_two__bottom_right);
    }
    if (direction & DIRECTION__EAST) {
        move_collision_manager__layer_two_east(
                &collision_manager->layer_two__top_left);
        move_collision_manager__layer_two_east(
                &collision_manager->layer_two__top_right);
        move_collision_manager__layer_two_east(
                &collision_manager->layer_two__bottom_left);
        move_collision_manager__layer_two_east(
                &collision_manager->layer_two__bottom_right);
    } else if (direction & DIRECTION__WEST) {
        move_collision_manager__layer_two_west(
                &collision_manager->layer_two__top_left);
        move_collision_manager__layer_two_west(
                &collision_manager->layer_two__top_right);
        move_collision_manager__layer_two_west(
                &collision_manager->layer_two__bottom_left);
        move_collision_manager__layer_two_west(
                &collision_manager->layer_two__bottom_right);
    }
}

void update_collision_manager__nodes_legal_directions__north(
        Collision_Manager *collision_manager,
        Game *game) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            i++) {

        current_node->legal_directions=
            current_node->collision_node__north->legal_directions;
        current_node->collision_node__north->legal_directions=
            current_node
            ->collision_node__north
            ->collision_node__north
            ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node, game);

        current_node =
            current_node->collision_node__east;
    }

    collision_manager->most_north_western__node =
        collision_manager->most_north_western__node
        ->collision_node__north;
}

void update_collision_manager__nodes_legal_directions__east(
        Collision_Manager *collision_manager,
        Game *game) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node
        ->collision_node__west;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            i++) {

        current_node->legal_directions=
            current_node
            ->collision_node__east
            ->legal_directions;
        current_node->collision_node__east->legal_directions=
            current_node
            ->collision_node__east
            ->collision_node__east
            ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node, game);

        current_node =
            current_node->collision_node__south;
    }

    collision_manager->most_north_western__node =
        collision_manager->most_north_western__node
        ->collision_node__east;
}

void update_collision_manager__nodes_legal_directions__south(
        Collision_Manager *collision_manager,
        Game *game) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node
        ->collision_node__north;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            i++) {

        current_node->legal_directions=
            current_node
            ->collision_node__south
            ->legal_directions;
        current_node->collision_node__south->legal_directions=
            current_node
            ->collision_node__south
            ->collision_node__south
            ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node, game);

        current_node =
            current_node->collision_node__east;
    }

    collision_manager->most_north_western__node =
        collision_manager
        ->most_north_western__node
        ->collision_node__south;
}

void update_collision_manager__nodes_legal_directions__west(
        Collision_Manager *collision_manager,
        Game *game) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            i++) {

        current_node->legal_directions=
            current_node
            ->collision_node__west
            ->legal_directions;
        current_node->collision_node__west->legal_directions=
            current_node
            ->collision_node__west
            ->collision_node__west
            ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node, game);

        current_node =
            current_node
            ->collision_node__south;
    }

    collision_manager->most_north_western__node =
        collision_manager->most_north_western__node
        ->collision_node__west;
}

void update_collision_manager__nodes_legal_directions(
        Collision_Manager *collision_manager,
        Direction direction_to_move_nodes,
        Game *game) {
    if (direction_to_move_nodes & DIRECTION__NORTH) {
        update_collision_manager__nodes_legal_directions__north(
                collision_manager,
                game);
    } else if (direction_to_move_nodes & DIRECTION__SOUTH) {
        update_collision_manager__nodes_legal_directions__south(
                collision_manager,
				game);
    }
    if (direction_to_move_nodes & DIRECTION__EAST) {
        update_collision_manager__nodes_legal_directions__east(
                collision_manager,
				game);
    } else if (direction_to_move_nodes & DIRECTION__WEST) {
        update_collision_manager__nodes_legal_directions__west(
                collision_manager,
				game);
    }
}

void update_collision_manager(
        Collision_Manager *collision_manager,
        World *world,
        Game *game) {

    Direction direction_to_move_nodes =
        DIRECTION__NONE;

    if (collision_manager->x__center_chunk 
            < world->chunk_manager.x__center_chunk) {
        direction_to_move_nodes |=
            DIRECTION__EAST;
    } else if (collision_manager->x__center_chunk 
            > world->chunk_manager.x__center_chunk) {
        direction_to_move_nodes |=
            DIRECTION__WEST;
    }

    if (collision_manager->y__center_chunk 
            < world->chunk_manager.y__center_chunk) {
        direction_to_move_nodes |=
            DIRECTION__NORTH;
    } else if (collision_manager->y__center_chunk 
            > world->chunk_manager.y__center_chunk) {
        direction_to_move_nodes |=
            DIRECTION__SOUTH;
    }

    move_collision_manager__nodes(
            collision_manager,
            direction_to_move_nodes);
    update_collision_manager__nodes_legal_directions(
            collision_manager, 
            direction_to_move_nodes,
            game);

    collision_manager->x__center_chunk =
        world->chunk_manager.x__center_chunk;
    collision_manager->y__center_chunk =
        world->chunk_manager.y__center_chunk;

    // debug_info("cm: %d, %d",
    //         collision_manager->x__center_chunk,
    //         collision_manager->y__center_chunk);

    update_collision_manager__layer_two(
            &collision_manager->layer_two__top_left, 
            collision_manager, 
            DIRECTION__NORTH_WEST);
    update_collision_manager__layer_two(
            &collision_manager->layer_two__top_right, 
            collision_manager, 
            DIRECTION__NORTH_EAST);
    update_collision_manager__layer_two(
            &collision_manager->layer_two__bottom_left, 
            collision_manager, 
            DIRECTION__SOUTH_EAST);
    update_collision_manager__layer_two(
            &collision_manager->layer_two__bottom_right, 
            collision_manager, 
            DIRECTION__SOUTH_WEST);
}
