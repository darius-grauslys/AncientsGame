#include <defines.h>
#include <collisions/collision_manager.h>
#include <debug/debug.h>
#include <collisions/hitbox_aabb.h>
#include <entity/entity.h>

#include <world/chunk_vectors.h>
#include <world/tile_vectors.h>

#warning See TODO
// TODO: prefix pointers with p_
// TODO: check if the below TODO still needs work
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

///
/// This is to only be called during
/// initalization, since layer_one
/// (x/y)__center_chunk__signed_index_i32 is
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
    Signed_Index__i32 x__chunk, 
    Signed_Index__i32 y__chunk) {
    x__chunk = x__chunk % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
    y__chunk = y__chunk % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
    if (x__chunk < 0) {
        x__chunk = (x__chunk + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW)
            % CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
    }
    if (y__chunk < 0) {
        y__chunk = (y__chunk + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS)
            % CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
    }
    return (CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS - y__chunk - 1)
        * CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW
        + x__chunk
        ;
}

void update_collision_manager__layer_three(
        Collision_Manager__Layer_Three *layer_three, 
        Collision_Manager__Layer_Two *layer_two,
        Direction__u8 quadrant_direction) {
    
    ///
    /// Magic numbers are justified here.
    /// We offset out (x/y)__center_chunk__signed_index_i32
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
            layer_three->x__center_chunk__signed_index_i32 =
                layer_two->x__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk__signed_index_i32 =
                layer_two->y__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__NORTH_WEST:
            layer_three->x__center_chunk__signed_index_i32 =
                layer_two->x__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk__signed_index_i32 =
                layer_two->y__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_EAST:
            layer_three->x__center_chunk__signed_index_i32 =
                layer_two->x__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk__signed_index_i32 =
                layer_two->y__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_WEST:
            layer_three->x__center_chunk__signed_index_i32 =
                layer_two->x__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            layer_three->y__center_chunk__signed_index_i32 =
                layer_two->y__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_THREE__CHUNK_CENTER_OFFSET;
            break;
    }
}

void update_collision_manager__layer_two(
        Collision_Manager__Layer_Two *layer_two, 
        Collision_Manager *collision_manager,
        Direction__u8 quadrant_direction) {
    switch (quadrant_direction) {
        default:
            debug_abort("Failed to update collision_manager \
bad quadrant_direction layer_two.");
            return;
        case DIRECTION__NORTH_EAST:
            layer_two->x__center_chunk__signed_index_i32 =
                collision_manager->x__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk__signed_index_i32 =
                collision_manager->y__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__NORTH_WEST:
            layer_two->x__center_chunk__signed_index_i32 =
                collision_manager->x__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk__signed_index_i32 =
                collision_manager->y__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_EAST:
            layer_two->x__center_chunk__signed_index_i32 =
                collision_manager->x__center_chunk__signed_index_i32
                + COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk__signed_index_i32 =
                collision_manager->y__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            break;
        case DIRECTION__SOUTH_WEST:
            layer_two->x__center_chunk__signed_index_i32 =
                collision_manager->x__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            layer_two->y__center_chunk__signed_index_i32 =
                collision_manager->y__center_chunk__signed_index_i32
                - COLLISION_MANAGER__LAYER_TWO__CHUNK_CENTER_OFFSET;
            break;
    }

    // debug_info("layer2: %d, %d",
    //         layer_two->x__center_chunk__signed_index_i32,
    //         layer_two->y__center_chunk__signed_index_i32);

    update_collision_manager__layer_three(
            &layer_two->top_left__layer_three, 
            layer_two, 
            DIRECTION__NORTH_WEST);
    update_collision_manager__layer_three(
            &layer_two->top_right__layer_three, 
            layer_two, 
            DIRECTION__NORTH_EAST);
    update_collision_manager__layer_three(
            &layer_two->bottom_left__layer_three, 
            layer_two, 
            DIRECTION__SOUTH_WEST);
    update_collision_manager__layer_three(
            &layer_two->bottom_right__layer_three, 
            layer_two, 
            DIRECTION__SOUTH_EAST);
}

void initialize_collision_manager__collision_node(
        Collision_Manager__Collision_Node *collision_node) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        collision_node->p_entity_ptrs[i] = 0;
    }
}

void initialize_collision_manager__layer_three(
        Collision_Manager__Layer_Three *layer_three,
        Collision_Manager *collision_manager) {

    layer_three->p_top_right__collision_node =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk__signed_index_i32, 
                    layer_three->y__center_chunk__signed_index_i32)
        ];
    layer_three->p_top_left__collision_node =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk__signed_index_i32 - 1, 
                    layer_three->y__center_chunk__signed_index_i32)
        ];
    layer_three->p_bottom_right__collision_node =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk__signed_index_i32, 
                    layer_three->y__center_chunk__signed_index_i32 - 1)
        ];
    layer_three->p_bottom_left__collision_node =
        &collision_manager->collision_nodes[
            get_collision_node_index_during__initialization(
                    layer_three->x__center_chunk__signed_index_i32 - 1, 
                    layer_three->y__center_chunk__signed_index_i32 - 1)
        ];
}

void initialize_collision_manager__layer_two(
        Collision_Manager__Layer_Two *layer_two,
        Collision_Manager *collision_manager,
        Direction__u8 quadrant_direction) {

    update_collision_manager__layer_two(
            layer_two, 
            collision_manager, 
            quadrant_direction);
    
    initialize_collision_manager__layer_three(
            &layer_two->top_left__layer_three, 
            collision_manager);
    initialize_collision_manager__layer_three(
            &layer_two->top_right__layer_three, 
            collision_manager);
    initialize_collision_manager__layer_three(
            &layer_two->bottom_left__layer_three, 
            collision_manager);
    initialize_collision_manager__layer_three(
            &layer_two->bottom_right__layer_three, 
            collision_manager);
}

void initialize_collision_manager(
        Collision_Manager *p_collision_manager) {
    p_collision_manager->x__center_chunk__signed_index_i32 =
        p_collision_manager->y__center_chunk__signed_index_i32 = 
        CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2;

    for (Quantity__u8 y=0; y < 
            CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS; y++) {
        for (Quantity__u8 x=0; x <
                CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW; x++) {
            Collision_Manager__Collision_Node *p_collision_node=
                &p_collision_manager->collision_nodes[
                get_collision_node_index_during__initialization(x, y)];

            initialize_collision_manager__collision_node(p_collision_node);

            Direction__u8 *p_node_legal_directions =
                &p_collision_node->legal_directions;
            *p_node_legal_directions = DIRECTION__NONE;

            // link west
            p_collision_node->p_west__collision_node =
                &p_collision_manager->collision_nodes[
                get_collision_node_index_during__initialization(
                        x-1, y)];
            if (x != 0) {
                *p_node_legal_directions |= DIRECTION__WEST;
            }
            // link east
            p_collision_node->p_east__collision_node =
                &p_collision_manager->collision_nodes[
                get_collision_node_index_during__initialization(
                        x+1, y)];
            if (x != CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW-1) {
                *p_node_legal_directions |= DIRECTION__EAST;
            }

            // y==0 -> y==7
            // link north
            p_collision_node->p_north__collision_node =
                &p_collision_manager->collision_nodes[
                get_collision_node_index_during__initialization(
                        x, y+1)];
            if (y != 0) {
                *p_node_legal_directions |= DIRECTION__NORTH;
            }
            // link south
            p_collision_node->p_south__collision_node =
                &p_collision_manager->collision_nodes[
                get_collision_node_index_during__initialization(
                        x, y-1)];
            if (y != CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS-1) {
                *p_node_legal_directions |= DIRECTION__SOUTH;
            }
        }
    }

    initialize_collision_manager__layer_two(
            &p_collision_manager->top_left__layer_two, 
            p_collision_manager, 
            DIRECTION__NORTH_WEST);
    initialize_collision_manager__layer_two(
            &p_collision_manager->top_right__layer_two, 
            p_collision_manager, 
            DIRECTION__NORTH_EAST);
    initialize_collision_manager__layer_two(
            &p_collision_manager->bottom_left__layer_two, 
            p_collision_manager, 
            DIRECTION__SOUTH_WEST);
    initialize_collision_manager__layer_two(
            &p_collision_manager->bottom_right__layer_two, 
            p_collision_manager, 
            DIRECTION__SOUTH_EAST);

    p_collision_manager->p_most_north_western__collision_node =
        &p_collision_manager->collision_nodes[0];
}

Collision_Manager__Collision_Node 
*get_collision_node_for__this_position(
        Collision_Manager *collision_manager,
        int32_t x__chunk,
        int32_t y__chunk
        ) {
    if (!is_in_bounds_of__collision_manager(
                collision_manager, x__chunk, y__chunk)) {
        debug_warning__verbose("get_collision_node_for__this_position, out of bounds.");
        return 0;
    }

    Collision_Manager__Layer_Two *layer_two;

    if (x__chunk <
            collision_manager->x__center_chunk__signed_index_i32) {
        if (y__chunk <
                collision_manager->y__center_chunk__signed_index_i32) {
            layer_two =
                &collision_manager->bottom_left__layer_two;
        } else {
            layer_two =
                &collision_manager->top_left__layer_two;
        }
    } else {
        if (y__chunk <
                collision_manager->y__center_chunk__signed_index_i32) {
            layer_two =
                &collision_manager->bottom_right__layer_two;
        } else {
            layer_two =
                &collision_manager->top_right__layer_two;
        }
    }

    Collision_Manager__Layer_Three *layer_three;

    if (x__chunk <
            layer_two->x__center_chunk__signed_index_i32) {
        if (y__chunk <
                layer_two->y__center_chunk__signed_index_i32) {
            layer_three =
                &layer_two->bottom_left__layer_three;
        } else {
            layer_three =
                &layer_two->top_left__layer_three;
        }
    } else {
        if (y__chunk <
                layer_two->y__center_chunk__signed_index_i32) {
            layer_three =
                &layer_two->bottom_right__layer_three;
        } else {
            layer_three =
                &layer_two->top_right__layer_three;
        }
    }

    Collision_Manager__Collision_Node *collision_node;

    if (x__chunk <
            layer_three->x__center_chunk__signed_index_i32) {
        if (y__chunk <
                layer_three->y__center_chunk__signed_index_i32) {
            collision_node =
                layer_three->p_bottom_left__collision_node;
        } else {
            collision_node =
                layer_three->p_top_left__collision_node;
        }
    } else {
        if (y__chunk <
                layer_three->y__center_chunk__signed_index_i32) {
            collision_node =
                layer_three->p_bottom_right__collision_node;
        } else {
            collision_node =
                layer_three->p_top_right__collision_node;
        }
    }

    return collision_node;
}

Direction__u8 is_this_entity_colliding_into__this_entity(
        Entity *entity_collision_source,
        Entity *entity_collided) {
    return is_hitbox__colliding(
            &entity_collision_source->hitbox, 
            &entity_collided->hitbox);
}

void check_collision_node_for__collisions(
        Collision_Manager__Collision_Node *collision_node,
        Game *p_game,
        Entity *entity,
        m_Entity_Collision_Handler f_entity_collision_handler) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        // All collisions checked.
        if (!collision_node->p_entity_ptrs[i]) {
            return;
        }

        if (collision_node->p_entity_ptrs[i] ==
                entity) {
            // Do not collide with yourself!
            continue;
        }

        Direction__u8 direction_of_collision =
            is_this_entity_colliding_into__this_entity(
            entity,
            collision_node->p_entity_ptrs[i]);
        if (direction_of_collision != DIRECTION__NONE) {
            if (f_entity_collision_handler) {
                f_entity_collision_handler(
                        entity,
                        collision_node->p_entity_ptrs[i],
                        direction_of_collision,
                        p_game);
            }
        }
    }
}

void poll_collision_node_and__neighbors(
        Collision_Manager__Collision_Node *p_collision_node,
        Game *p_game,
        Entity *p_entity,
        m_Entity_Collision_Handler f_entity_collision_handler) {
    check_collision_node_for__collisions(
            p_collision_node, 
            p_game,
            p_entity,
            f_entity_collision_handler);

    // north
    if (p_collision_node->legal_directions & DIRECTION__NORTH) {
        check_collision_node_for__collisions(
                p_collision_node->p_north__collision_node, 
                p_game,
                p_entity,
                f_entity_collision_handler);
        // north east
        if (p_collision_node->legal_directions & DIRECTION__EAST) {
            check_collision_node_for__collisions(
                    p_collision_node->p_north__collision_node
                        ->p_east__collision_node, 
                    p_game,
                    p_entity,
                    f_entity_collision_handler);
        }
        // north west
        if (p_collision_node->legal_directions & DIRECTION__WEST) {
            check_collision_node_for__collisions(
                    p_collision_node->p_north__collision_node
                        ->p_west__collision_node, 
                    p_game,
                    p_entity,
                    f_entity_collision_handler);
        }
    }
    // south
    if (p_collision_node->legal_directions & DIRECTION__SOUTH) {
        check_collision_node_for__collisions(
                p_collision_node->p_south__collision_node, 
                p_game,
                p_entity,
                f_entity_collision_handler);
        // south east
        if (p_collision_node->legal_directions & DIRECTION__EAST) {
            check_collision_node_for__collisions(
                    p_collision_node->p_south__collision_node
                        ->p_east__collision_node, 
                    p_game,
                    p_entity,
                    f_entity_collision_handler);
        }
        // south west
        if (p_collision_node->legal_directions & DIRECTION__WEST) {
            check_collision_node_for__collisions(
                    p_collision_node->p_south__collision_node
                        ->p_west__collision_node, 
                    p_game,
                    p_entity,
                    f_entity_collision_handler);
        }
    }
    // east
    if (p_collision_node->legal_directions & DIRECTION__EAST) {
        check_collision_node_for__collisions(
                p_collision_node->p_east__collision_node, 
                p_game,
                p_entity,
                f_entity_collision_handler);
    }
    // west
    if (p_collision_node->legal_directions & DIRECTION__WEST) {
        check_collision_node_for__collisions(
                p_collision_node->p_west__collision_node, 
                p_game,
                p_entity,
                f_entity_collision_handler);
    }
}

bool poll_collision_manager(
        Collision_Manager *collision_manager,
        Game *p_game,
        Entity *entity,
        m_Entity_Collision_Handler f_entity_collision_handler) {
    Chunk_Vector__3i32 chunk_vector__3i32 =
        vector_3i32F4_to__chunk_vector_3i32(
                entity->hitbox.position__3i32F4);
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                chunk_vector__3i32.x__i32,
                chunk_vector__3i32.y__i32);

    if (!collision_node) {
        return false;
    }

    poll_collision_node_and__neighbors(
            collision_node, 
            p_game,
            entity,
            f_entity_collision_handler);

    return true;
}

void remove_entity_from__collision_node(
        Collision_Manager__Collision_Node *p_collision_node,
        Entity *p_entity) {

    if (!p_collision_node->p_entity_ptrs[0]) {
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

    Entity **p_removed_entity_ptr_slot = 0;
    Entity **p_last_entity_ptr_slot = 0;
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        if (p_collision_node->p_entity_ptrs[i] == p_entity) {
            p_removed_entity_ptr_slot =
                &p_collision_node->p_entity_ptrs[i];
            break;
        }
    }
    for (int32_t i=ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE-1;
            i>=0;i--) {
        if (p_collision_node->p_entity_ptrs[i]) {
            p_last_entity_ptr_slot =
                &p_collision_node->p_entity_ptrs[i];
            break;
        }
    }

    if (!p_removed_entity_ptr_slot) {
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

    if (*p_removed_entity_ptr_slot == *p_last_entity_ptr_slot) {
        *p_removed_entity_ptr_slot = 0;
        return;
    }
    // Keep the entity array tightly packed.
    // Order doesn't matter.
    *p_removed_entity_ptr_slot =
        *p_last_entity_ptr_slot;
    *p_last_entity_ptr_slot = 0;
}

Entity *get_p_entity_from__collision_manager_with__3i32F4(
        Collision_Manager *p_collision_manager,
        Vector__3i32F4 position__3i32F4) {
    Chunk_Vector__3i32 chunk_vector__3i32 =
        vector_3i32F4_to__chunk_vector_3i32(
                position__3i32F4);
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                p_collision_manager, 
                chunk_vector__3i32.x__i32,
                chunk_vector__3i32.y__i32);

    if (!collision_node)
        return 0;

    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        Entity *p_entity =
            collision_node->p_entity_ptrs[i];
        // All collisions checked.
        if (!p_entity) {
            return 0;
        }

        bool is_hitbox_containing__our_position =
            is_vector_3i32F4_inside__hitbox(
                    position__3i32F4, 
                    &p_entity->hitbox);
        if (is_hitbox_containing__our_position)
            return p_entity;
    }
    return 0;
}

void foreach_p_entity_within__hitbox(
        Collision_Manager *p_collision_manager,
        Hitbox_AABB *p_hitbox,
        f_Foreach_Entity_Within f_callback,
        Game *p_game,
        void *p_data) {
    Chunk_Vector__3i32 chunk_vector__3i32 =
        vector_3i32F4_to__chunk_vector_3i32(
                p_hitbox->position__3i32F4);
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                p_collision_manager, 
                chunk_vector__3i32.x__i32,
                chunk_vector__3i32.y__i32);

    if (!collision_node)
        return;

    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        Entity *p_entity =
            collision_node->p_entity_ptrs[i];
        // All collisions checked.
        if (!p_entity) {
            return;
        }

        bool is_entity_overlapping__hitbox =
            is_this_hitbox__overlapping_this_hitbox(
                    &p_entity->hitbox,
                    p_hitbox);
        if (is_entity_overlapping__hitbox) {
            f_callback(
                    p_entity,
                    p_game,
                    p_data);
        }
    }
    return;
}

///
/// This is called because the node "fell off" the map.
///
void unload_all_entities_from__collision_node(
        Collision_Manager__Collision_Node *collision_node) {
    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        collision_node->p_entity_ptrs[i] = 0;
    }
}

void add_entity_to__collision_node(
        Collision_Manager__Collision_Node *collision_node,
        Entity *entity) {
    // we should always have enough room.

    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            i++) {
        if (collision_node->p_entity_ptrs[i] == entity) {
            return;
        }
        if (!collision_node->p_entity_ptrs[i]) {
            collision_node->p_entity_ptrs[i] =
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
    Chunk_Vector__3i32 chunk_vector__3i32 =
        vector_3i32F4_to__chunk_vector_3i32(
                entity->hitbox.position__3i32F4);
    Collision_Manager__Collision_Node *collision_node =
        get_collision_node_for__this_position(
                collision_manager, 
                chunk_vector__3i32.x__i32,
                chunk_vector__3i32.y__i32);

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
    for (Index__u32 index=0;
            index<ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE;
            index++) {
        if (node->p_entity_ptrs[index] == entity)
            return true;
    }
    return false;
}

void remove_entity_from__collision_manager__at(
        Collision_Manager *collision_manager,
        Entity *entity,
        Chunk_Vector__3i32 chunk_vector__3i32) {
    Signed_Index__i32 old_x__chunk =
        chunk_vector__3i32.x__i32;
    Signed_Index__i32 old_y__chunk =
        chunk_vector__3i32.y__i32;
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
#ifndef NDEBUG
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
#endif

    remove_entity_from__collision_node(
            collision_node, entity);
}

static void inline move_collision_node__north(
        Collision_Manager__Collision_Node **p_collision_node_ptr) {
    *p_collision_node_ptr =
        (*p_collision_node_ptr)->p_north__collision_node;
}
static void inline move_collision_node__east(
        Collision_Manager__Collision_Node **p_collision_node_ptr) {
    *p_collision_node_ptr =
        (*p_collision_node_ptr)->p_east__collision_node;
}
static void inline move_collision_node__south(
        Collision_Manager__Collision_Node **p_collision_node_ptr) {
    *p_collision_node_ptr =
        (*p_collision_node_ptr)->p_south__collision_node;
}
static void inline move_collision_node__west(
        Collision_Manager__Collision_Node **p_collision_node_ptr) {
    *p_collision_node_ptr =
        (*p_collision_node_ptr)->p_west__collision_node;
}

static void inline move_collision_manager__layer_three_north(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__north(
        &layer_three
            ->p_top_left__collision_node);
    move_collision_node__north(
        &layer_three
            ->p_top_right__collision_node);
    move_collision_node__north(
        &layer_three
            ->p_bottom_left__collision_node);
    move_collision_node__north(
        &layer_three
            ->p_bottom_right__collision_node);
}

static void inline move_collision_manager__layer_three_east(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__east(
        &layer_three
            ->p_top_left__collision_node);
    move_collision_node__east(
        &layer_three
            ->p_top_right__collision_node);
    move_collision_node__east(
        &layer_three
            ->p_bottom_left__collision_node);
    move_collision_node__east(
        &layer_three
            ->p_bottom_right__collision_node);
}

static void inline move_collision_manager__layer_three_south(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__south(
        &layer_three
            ->p_top_left__collision_node);
    move_collision_node__south(
        &layer_three
            ->p_top_right__collision_node);
    move_collision_node__south(
        &layer_three
            ->p_bottom_left__collision_node);
    move_collision_node__south(
        &layer_three
            ->p_bottom_right__collision_node);
}

static void inline move_collision_manager__layer_three_west(
        Collision_Manager__Layer_Three *layer_three) {
    move_collision_node__west(
        &layer_three
            ->p_top_left__collision_node);
    move_collision_node__west(
        &layer_three
            ->p_top_right__collision_node);
    move_collision_node__west(
        &layer_three
            ->p_bottom_left__collision_node);
    move_collision_node__west(
        &layer_three
            ->p_bottom_right__collision_node);
}

void move_collision_manager__layer_two_north(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_north(
            &layer_two->top_left__layer_three);
    move_collision_manager__layer_three_north(
            &layer_two->top_right__layer_three);
    move_collision_manager__layer_three_north(
            &layer_two->bottom_left__layer_three);
    move_collision_manager__layer_three_north(
            &layer_two->bottom_right__layer_three);
}

void move_collision_manager__layer_two_east(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_east(
            &layer_two->top_left__layer_three);
    move_collision_manager__layer_three_east(
            &layer_two->top_right__layer_three);
    move_collision_manager__layer_three_east(
            &layer_two->bottom_left__layer_three);
    move_collision_manager__layer_three_east(
            &layer_two->bottom_right__layer_three);
}

void move_collision_manager__layer_two_south(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_south(
            &layer_two->top_left__layer_three);
    move_collision_manager__layer_three_south(
            &layer_two->top_right__layer_three);
    move_collision_manager__layer_three_south(
            &layer_two->bottom_left__layer_three);
    move_collision_manager__layer_three_south(
            &layer_two->bottom_right__layer_three);
}

void move_collision_manager__layer_two_west(
        Collision_Manager__Layer_Two *layer_two) {
    move_collision_manager__layer_three_west(
            &layer_two->top_left__layer_three);
    move_collision_manager__layer_three_west(
            &layer_two->top_right__layer_three);
    move_collision_manager__layer_three_west(
            &layer_two->bottom_left__layer_three);
    move_collision_manager__layer_three_west(
            &layer_two->bottom_right__layer_three);
}

void move_collision_manager__nodes(
        Collision_Manager *collision_manager,
        Direction__u8 direction) {
    if (direction & DIRECTION__NORTH) {
        move_collision_manager__layer_two_north(
                &collision_manager->top_left__layer_two);
        move_collision_manager__layer_two_north(
                &collision_manager->top_right__layer_two);
        move_collision_manager__layer_two_north(
                &collision_manager->bottom_left__layer_two);
        move_collision_manager__layer_two_north(
                &collision_manager->bottom_right__layer_two);
        collision_manager->p_most_north_western__collision_node =
            collision_manager->p_most_north_western__collision_node
            ->p_north__collision_node;
    } else if (direction & DIRECTION__SOUTH) {
        move_collision_manager__layer_two_south(
                &collision_manager->top_left__layer_two);
        move_collision_manager__layer_two_south(
                &collision_manager->top_right__layer_two);
        move_collision_manager__layer_two_south(
                &collision_manager->bottom_left__layer_two);
        move_collision_manager__layer_two_south(
                &collision_manager->bottom_right__layer_two);
        collision_manager->p_most_north_western__collision_node =
            collision_manager->p_most_north_western__collision_node
            ->p_south__collision_node;
    }
    if (direction & DIRECTION__EAST) {
        move_collision_manager__layer_two_east(
                &collision_manager->top_left__layer_two);
        move_collision_manager__layer_two_east(
                &collision_manager->top_right__layer_two);
        move_collision_manager__layer_two_east(
                &collision_manager->bottom_left__layer_two);
        move_collision_manager__layer_two_east(
                &collision_manager->bottom_right__layer_two);
        collision_manager->p_most_north_western__collision_node =
            collision_manager->p_most_north_western__collision_node
            ->p_east__collision_node;
    } else if (direction & DIRECTION__WEST) {
        move_collision_manager__layer_two_west(
                &collision_manager->top_left__layer_two);
        move_collision_manager__layer_two_west(
                &collision_manager->top_right__layer_two);
        move_collision_manager__layer_two_west(
                &collision_manager->bottom_left__layer_two);
        move_collision_manager__layer_two_west(
                &collision_manager->bottom_right__layer_two);
        collision_manager->p_most_north_western__collision_node =
            collision_manager->p_most_north_western__collision_node
            ->p_west__collision_node;
    }
}

void update_collision_manager__nodes_legal_directions__north(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *p_current_node =
        collision_manager->p_most_north_western__collision_node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            i++) {

        p_current_node
            ->p_north__collision_node
            ->p_north__collision_node
            ->legal_directions =
                p_current_node
                ->p_north__collision_node
                ->legal_directions;
        p_current_node
            ->p_north__collision_node
            ->legal_directions =
                p_current_node
                ->legal_directions;
        p_current_node
            ->legal_directions=
                p_current_node
                ->p_south__collision_node
                ->legal_directions;

        unload_all_entities_from__collision_node(
                p_current_node);

        p_current_node =
            p_current_node->p_east__collision_node;
    }
}

void update_collision_manager__nodes_legal_directions__east(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *p_current_node =
        collision_manager
        ->p_most_north_western__collision_node
        ->p_west__collision_node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            i++) {

        p_current_node->p_east__collision_node->legal_directions=
            p_current_node
            ->legal_directions;
        p_current_node->legal_directions=
            p_current_node
            ->p_west__collision_node
            ->legal_directions;

        unload_all_entities_from__collision_node(
                p_current_node);

        p_current_node =
            p_current_node->p_south__collision_node;
    }
}

void update_collision_manager__nodes_legal_directions__south(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *p_current_node =
        collision_manager->p_most_north_western__collision_node
        ->p_north__collision_node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW;
            i++) {

        p_current_node->p_south__collision_node->legal_directions=
            p_current_node
            ->legal_directions;
        p_current_node->legal_directions=
            p_current_node
            ->p_north__collision_node
            ->legal_directions;

        unload_all_entities_from__collision_node(
                p_current_node);

        p_current_node =
            p_current_node->p_east__collision_node;
    }
}

void update_collision_manager__nodes_legal_directions__west(
        Collision_Manager *collision_manager) {
    Collision_Manager__Collision_Node *p_current_node =
        collision_manager->p_most_north_western__collision_node;
    for (uint32_t i=0;
            i<CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS;
            i++) {

        p_current_node->p_west__collision_node->legal_directions=
            p_current_node
            ->legal_directions;
        p_current_node->legal_directions=
            p_current_node
            ->p_east__collision_node
            ->legal_directions;

        unload_all_entities_from__collision_node(
                p_current_node);

        p_current_node =
            p_current_node
            ->p_south__collision_node;
    }
}

void update_collision_manager__nodes_legal_directions(
        Collision_Manager *collision_manager,
        Direction__u8 direction_to_move_nodes) {
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

void set_collision_manager__center_chunk(
        Collision_Manager *collision_manager,
        int32_t x__center_chunk__signed_index_i32,
        int32_t y__center_chunk__signed_index_i32) {

    while (collision_manager->x__center_chunk__signed_index_i32
            != x__center_chunk__signed_index_i32
            || collision_manager->y__center_chunk__signed_index_i32
            != y__center_chunk__signed_index_i32) {
        Direction__u8 direction_to_move_nodes =
            DIRECTION__NONE;
        if (collision_manager->x__center_chunk__signed_index_i32 
                < x__center_chunk__signed_index_i32) {
            collision_manager->x__center_chunk__signed_index_i32++;
            direction_to_move_nodes |=
                DIRECTION__EAST;
        } else if (collision_manager->x__center_chunk__signed_index_i32 
                > x__center_chunk__signed_index_i32) {
            collision_manager->x__center_chunk__signed_index_i32--;
            direction_to_move_nodes |=
                DIRECTION__WEST;
        }

        if (collision_manager->y__center_chunk__signed_index_i32 
                < y__center_chunk__signed_index_i32) {
            collision_manager->y__center_chunk__signed_index_i32++;
            direction_to_move_nodes |=
                DIRECTION__NORTH;
        } else if (collision_manager->y__center_chunk__signed_index_i32 
                > y__center_chunk__signed_index_i32) {
            collision_manager->y__center_chunk__signed_index_i32--;
            direction_to_move_nodes |=
                DIRECTION__SOUTH;
        }

        move_collision_manager__nodes(
                collision_manager,
                direction_to_move_nodes);
        update_collision_manager__nodes_legal_directions(
                collision_manager, 
                direction_to_move_nodes);
    }

    // debug_info("cm: %d, %d",
    //         collision_manager->x__center_chunk__signed_index_i32,
    //         collision_manager->y__center_chunk__signed_index_i32);

    update_collision_manager__layer_two(
            &collision_manager->top_left__layer_two, 
            collision_manager, 
            DIRECTION__NORTH_WEST);
    update_collision_manager__layer_two(
            &collision_manager->top_right__layer_two, 
            collision_manager, 
            DIRECTION__NORTH_EAST);
    update_collision_manager__layer_two(
            &collision_manager->bottom_left__layer_two, 
            collision_manager, 
            DIRECTION__SOUTH_WEST);
    update_collision_manager__layer_two(
            &collision_manager->bottom_right__layer_two, 
            collision_manager, 
            DIRECTION__SOUTH_EAST);
}
