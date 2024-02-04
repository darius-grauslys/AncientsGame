#include <collisions/collision_manager.h>
#include <debug/debug.h>
#include <collisions/hitbox_aabb.h>
#include <entity/entity.h>

#warning See TODO
// TODO: this currently wont work for 
// CHUNK_MANAGER__QUANTITY_OF_CHUNKS != 8x8
// To fix this, keep collision_manager.collision_nodes at 8x8
// and map get_collision_node_index_during__initialization(...)
// accordingly based on the dimension discrepencies betwen
// Collision_Manager and Chunk_Manager.

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
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__NORTH_WEST:
            layer_three->x__center_chunk =
                layer_two->x__center_chunk
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_EAST:
            layer_three->x__center_chunk =
                layer_two->x__center_chunk
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_WEST:
            layer_three->x__center_chunk =
                layer_two->x__center_chunk
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk =
                layer_two->y__center_chunk
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
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
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__NORTH_WEST:
            layer_two->x__center_chunk =
                collision_manager->x__center_chunk
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_EAST:
            layer_two->x__center_chunk =
                collision_manager->x__center_chunk
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_WEST:
            layer_two->x__center_chunk =
                collision_manager->x__center_chunk
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk =
                collision_manager->y__center_chunk
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
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
            DIRECTION__SOUTH_WEST);
    update_collision_manager__layer_three(
            &layer_two->layer_three__bottom_right, 
            layer_two, 
            DIRECTION__SOUTH_EAST);
}

void init_collision_manager__collision_node(
        Collision_Manager__Collision_Node *collision_node) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        collision_node->entity_ptrs[i] = 0;
    }
}

void init_collision_manager__layer_three(
        Collision_Manager__Layer_Three *layer_three,
        Collision_Manager *collision_manager) {

    layer_three->collision_node__top_right =
        &collision_manager->collision_nodes[
            get_chunk_index_during__initialization(
                    layer_three->x__center_chunk, 
                    layer_three->y__center_chunk)
        ];
    layer_three->collision_node__top_left =
        &collision_manager->collision_nodes[
            get_chunk_index_during__initialization(
                    layer_three->x__center_chunk - 1, 
                    layer_three->y__center_chunk)
        ];
    layer_three->collision_node__bottom_right =
        &collision_manager->collision_nodes[
            get_chunk_index_during__initialization(
                    layer_three->x__center_chunk, 
                    layer_three->y__center_chunk - 1)
        ];
    layer_three->collision_node__bottom_left =
        &collision_manager->collision_nodes[
            get_chunk_index_during__initialization(
                    layer_three->x__center_chunk - 1, 
                    layer_three->y__center_chunk - 1)
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
            collision_manager);
    init_collision_manager__layer_three(
            &layer_two->layer_three__top_right, 
            collision_manager);
    init_collision_manager__layer_three(
            &layer_two->layer_three__bottom_left, 
            collision_manager);
    init_collision_manager__layer_three(
            &layer_two->layer_three__bottom_right, 
            collision_manager);
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
                get_chunk_index_during__initialization(x, y)];

            init_collision_manager__collision_node(collision_node);

            Direction *node_legal_directions =
                &collision_node->legal_directions;
            *node_legal_directions = DIRECTION__NONE;

            // link west
            collision_node->collision_node__west =
                &collision_manager->collision_nodes[
                get_chunk_index_during__initialization(
                        x-1, y)];
            if (x != 0) {
                *node_legal_directions |= DIRECTION__WEST;
            }
            // link east
            collision_node->collision_node__east =
                &collision_manager->collision_nodes[
                get_chunk_index_during__initialization(
                        x+1, y)];
            if (x != CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW-1) {
                *node_legal_directions |= DIRECTION__EAST;
            }

            // y==0 -> y==7
            // link north
            collision_node->collision_node__north =
                &collision_manager->collision_nodes[
                get_chunk_index_during__initialization(
                        x, y+1)];
            if (y != 0) {
                *node_legal_directions |= DIRECTION__NORTH;
            }
            // link south
            collision_node->collision_node__south =
                &collision_manager->collision_nodes[
                get_chunk_index_during__initialization(
                        x, y-1)];
            if (y != CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS-1) {
                *node_legal_directions |= DIRECTION__SOUTH;
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
            DIRECTION__SOUTH_WEST);
    init_collision_manager__layer_two(
            &collision_manager->layer_two__bottom_right, 
            collision_manager, 
            DIRECTION__SOUTH_EAST);

    collision_manager->most_north_western__node =
        &collision_manager->collision_nodes[0];
}

Collision_Manager__Collision_Node 
*get_collision_node_for__this_position(
        Collision_Manager *collision_manager,
        int32_t x__chunk,
        int32_t y__chunk
        ) {
    if (!is_in_bounds_of__collision_manager(
                collision_manager, x__chunk, y__chunk))
        return 0;

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

Direction is_this_entity_colliding_into__this_entity(
        Entity *entity_collision_source,
        Entity *entity_collided) {
    return is_hitbox__colliding(
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

        Direction direction_of_collision =
            is_this_entity_colliding_into__this_entity(
            entity,
            collision_node->entity_ptrs[i]);
        if (direction_of_collision != DIRECTION__NONE) {
            if (entity->collision_handler) {
                entity->collision_handler(entity,
                        collision_node->entity_ptrs[i],
                        direction_of_collision);
            }
        }
    }
}

bool poll_collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity) {
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                entity->hitbox.x__chunk,
                entity->hitbox.y__chunk);

    if (!collision_node) {
        return false;
    }

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

    return true;
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
            break;
        }
    }
    for (int32_t i=ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE-1;
            i>=0;i--) {
        if (collision_node->entity_ptrs[i]) {
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

    if (*removed_entity_ptr_slot == *last_entity_ptr_slot) {
        *removed_entity_ptr_slot = 0;
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
        Collision_Manager__Collision_Node *collision_node) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        collision_node->entity_ptrs[i] = 0;
    }
}

void add_entity_to__collision_node(
        Collision_Manager__Collision_Node *collision_node,
        Entity *entity) {
    // we should always have enough room.

    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        if (collision_node->entity_ptrs[i] == entity) {
            return;
        }
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

bool add_entity_to__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity) {
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                entity->hitbox.x__chunk,
                entity->hitbox.y__chunk);

    if (!collision_node)
        return false;

    // debug_info("added entity to node: %d, %d",
    //         collision_node->x__chunk,
    //         collision_node->y__chunk);
    add_entity_to__collision_node(
            collision_node, entity);

    return true;
}

// remove later:
bool DEBUG_is_in_node(Collision_Manager__Collision_Node *node,
        Entity *entity) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        if (node->entity_ptrs[i] == entity)
            return true;
    }
    return false;
}

void remove_entity_from__collision_manager__at(
        Collision_Manager *collision_manager,
        Entity *entity,
        int32_t old_x__chunk,
        int32_t old_y__chunk) {
    // debug_info("remove entity from collision_node: %d, %d where manager is: %d, %d",
    //         old_x__chunk,
    //         old_y__chunk,
    //         collision_manager->x__center_chunk,
    //         collision_manager->y__center_chunk);
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                old_x__chunk,
                old_y__chunk);

    if (!collision_node) {
        debug_error("remove_entity_from__collision_manager__at: \
out of bounds: (%d, %d)", old_x__chunk, old_y__chunk);
        return;
    }

    //for debug
    if (!DEBUG_is_in_node(collision_node, entity)) {
        debug_error("remove_entity_from__collision_manager__at: \
node is empty: (%d, %d)", old_x__chunk, old_y__chunk);
        debug_info("searching for entity...");
        for (uint32_t i=0;i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS;i++) {
            Collision_Manager__Collision_Node *node =
                &collision_manager->collision_nodes[i];
            if (DEBUG_is_in_node(node, entity)) {
                debug_warning("found: (%d, %d)",
                        i % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW,
                        i / CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW);
                return;
            }
        }
        debug_error("entity not found!");
        return; 
    }

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

void update_collision_manager__nodes_legal_directions__north(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            i++) {

        current_node
            ->collision_node__north
            ->collision_node__north
            ->legal_directions =
                current_node
                ->collision_node__north
                ->legal_directions;
        current_node
            ->collision_node__north
            ->legal_directions =
                current_node
                ->legal_directions;
        current_node
            ->legal_directions=
                current_node->
                collision_node__south
                ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node);

        current_node =
            current_node->collision_node__east;
    }
}

void update_collision_manager__nodes_legal_directions__east(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node
        ->collision_node__west;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            i++) {

        current_node->collision_node__east->legal_directions=
            current_node
            ->legal_directions;
        current_node->legal_directions=
            current_node
            ->collision_node__west
            ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node);

        current_node =
            current_node->collision_node__south;
    }
}

void update_collision_manager__nodes_legal_directions__south(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node
        ->collision_node__north;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            i++) {

        current_node->collision_node__south->legal_directions=
            current_node
            ->legal_directions;
        current_node->legal_directions=
            current_node
            ->collision_node__north
            ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node);

        current_node =
            current_node->collision_node__east;
    }
}

void update_collision_manager__nodes_legal_directions__west(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *current_node =
        collision_manager->most_north_western__node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            i++) {

        current_node->collision_node__west->legal_directions=
            current_node
            ->legal_directions;
        current_node->legal_directions=
            current_node
            ->collision_node__east
            ->legal_directions;

        unload_all_entities_from__collision_node(
                current_node);

        current_node =
            current_node
            ->collision_node__south;
    }
}

void update_collision_manager__nodes_legal_directions(
        Collision_Manager *collision_manager,
        Direction direction_to_move_nodes) {
    if (direction_to_move_nodes & DIRECTION__NORTH) {
        update_collision_manager__nodes_legal_directions__north(
                collision_manager);
    } else if (direction_to_move_nodes & DIRECTION__SOUTH) {
        update_collision_manager__nodes_legal_directions__south(
                collision_manager);
    }
    if (direction_to_move_nodes & DIRECTION__EAST) {
        update_collision_manager__nodes_legal_directions__east(
                collision_manager);
    } else if (direction_to_move_nodes & DIRECTION__WEST) {
        update_collision_manager__nodes_legal_directions__west(
                collision_manager);
    }
}

void move_collision_manager(
        Collision_Manager *collision_manager,
        Direction direction,
        uint32_t steps) {

    for (uint32_t current__step=0;current__step<steps;current__step++) {
        if (direction & DIRECTION__NORTH) {
            move_collision_manager__layer_two_north(
                    &collision_manager->layer_two__top_left);
            move_collision_manager__layer_two_north(
                    &collision_manager->layer_two__top_right);
            move_collision_manager__layer_two_north(
                    &collision_manager->layer_two__bottom_left);
            move_collision_manager__layer_two_north(
                    &collision_manager->layer_two__bottom_right);
            collision_manager->most_north_western__node =
                collision_manager->most_north_western__node
                ->collision_node__north;
            collision_manager->y__center_chunk++;
        } else if (direction & DIRECTION__SOUTH) {
            move_collision_manager__layer_two_south(
                    &collision_manager->layer_two__top_left);
            move_collision_manager__layer_two_south(
                    &collision_manager->layer_two__top_right);
            move_collision_manager__layer_two_south(
                    &collision_manager->layer_two__bottom_left);
            move_collision_manager__layer_two_south(
                    &collision_manager->layer_two__bottom_right);
            collision_manager->most_north_western__node =
                collision_manager->most_north_western__node
                ->collision_node__south;
            collision_manager->y__center_chunk--;
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
            collision_manager->most_north_western__node =
                collision_manager->most_north_western__node
                ->collision_node__east;
            collision_manager->x__center_chunk++;
        } else if (direction & DIRECTION__WEST) {
            move_collision_manager__layer_two_west(
                    &collision_manager->layer_two__top_left);
            move_collision_manager__layer_two_west(
                    &collision_manager->layer_two__top_right);
            move_collision_manager__layer_two_west(
                    &collision_manager->layer_two__bottom_left);
            move_collision_manager__layer_two_west(
                    &collision_manager->layer_two__bottom_right);
            collision_manager->most_north_western__node =
                collision_manager->most_north_western__node
                ->collision_node__west;
            collision_manager->x__center_chunk--;
        }

        update_collision_manager__nodes_legal_directions(
                collision_manager, 
                direction);
    }

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
            DIRECTION__SOUTH_WEST);
    update_collision_manager__layer_two(
            &collision_manager->layer_two__bottom_right, 
            collision_manager, 
            DIRECTION__SOUTH_EAST);
}

void set_collision_manager_at__position(
        Collision_Manager *collision_manager,
        int32_t x__center_chunk,
        int32_t y__center_chunk) {
    int32_t local_x__current__center_chunk =
        get_chunk_mod_index(collision_manager->x__center_chunk);

    int32_t local_y__current__center_chunk =
        get_chunk_mod_index(collision_manager->y__center_chunk);

    int32_t local_x__new__center_chunk =
        get_chunk_mod_index(x__center_chunk);
    int32_t local_y__new__center_chunk =
        get_chunk_mod_index(y__center_chunk);

    while (local_x__new__center_chunk
            !=
            local_x__current__center_chunk) {
        if (local_x__new__center_chunk
                < local_x__current__center_chunk) {
            local_x__current__center_chunk--;
            move_collision_manager(
                    collision_manager,
                    DIRECTION__WEST,
                    1);
        } else {
            local_x__current__center_chunk++;
            move_collision_manager(
                    collision_manager,
                    DIRECTION__EAST,
                    1);
        }
    }

    // TODO: figure out why this needs a -1
    while (local_y__new__center_chunk - 1
            !=
            local_y__current__center_chunk) {
        if (local_y__new__center_chunk - 1
                < local_y__current__center_chunk) {
            local_y__current__center_chunk--;
            move_collision_manager(
                    collision_manager,
                    DIRECTION__SOUTH,
                    1);
        } else {
            local_y__current__center_chunk++;
            move_collision_manager(
                    collision_manager,
                    DIRECTION__NORTH,
                    1);
        }
    }

    collision_manager->x__center_chunk =
        x__center_chunk;
    collision_manager->y__center_chunk =
        y__center_chunk;

    // Start at most SE
    Collision_Manager__Collision_Node
        *origin__collision_node =
        &collision_manager
        ->layer_two__bottom_left
        .layer_three__bottom_left
        .collision_node__bottom_left
        ;
    Collision_Manager__Collision_Node
        *current__collision_node = 
        origin__collision_node;

    for (int32_t y=-CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
            y<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS/2;
            y++) {
        for (int32_t x=-CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW/2;
                x++) {
            unload_all_entities_from__collision_node(current__collision_node);
            current__collision_node =
                current__collision_node
                ->collision_node__east;
        }
        origin__collision_node =
            origin__collision_node
            ->collision_node__north;
        current__collision_node =
            origin__collision_node;
    }
}
