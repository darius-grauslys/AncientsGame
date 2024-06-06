#ifndef HITBOX_AABB_H
#define HITBOX_AABB_H

#include <defines.h>

Direction__u8 is_hitbox__colliding(
        Hitbox_AABB *hitbox__checking,
        Hitbox_AABB *hitbox__other);

void get_points_aabb_from__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb);

static Signed_Index__i32 inline get_global_x_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->chunk_index__3i32.x__i32) 
     << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->position__3i32F4.x__i32F4 + hitbox->velocity__3i32F4.x__i32F4) 
                >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        ;
}

static Signed_Index__i32 inline get_global_y_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->chunk_index__3i32.y__i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->position__3i32F4.y__i32F4 + hitbox->velocity__3i32F4.y__i32F4) 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE))
    ;
}

static Signed_Index__i32 inline get_global_z_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->chunk_index__3i32.z__i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->position__3i32F4.z__i32F4 + hitbox->velocity__3i32F4.z__i32F4) 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE))
    ;
}

static Signed_Index__i32 inline get_global_x_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->chunk_index__3i32.x__i32) 
     << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->position__3i32F4.x__i32F4) 
                >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        ;
}

static Signed_Index__i32 inline get_global_y_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->chunk_index__3i32.y__i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->position__3i32F4.y__i32F4) 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE))
    ;
}

static Signed_Index__i32 inline get_global_z_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->chunk_index__3i32.z__i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->position__3i32F4.z__i32F4) 
            >> FRACTIONAL_PERCISION_4__BIT_SIZE))
    ;
}

void commit_hitbox_velocity(
        Hitbox_AABB *hitbox);

/// If the hitbox resides in an entity which is
/// registered to the collision system, DO NOT invoke this.
/// Instead invoke using game_action.h .
///
void set_hitbox__position_with__3i32F4(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 position__3i32F4);

/// If the hitbox resides in an entity which is
/// registered to the collision system, DO NOT invoke this.
/// Instead invoke using game_action.h .
///
void set_hitbox__position_with__3i32(
        Hitbox_AABB *hitbox,
        Vector__3i32 position__3i32);

static Direction__u8 inline get_movement_direction_of__hitbox(
        Hitbox_AABB *hitbox) {
    Direction__u8 direction_of_movement =
        DIRECTION__NONE;
    if (0 < hitbox->velocity__3i32F4.x__i32F4) {
        direction_of_movement |= DIRECTION__EAST;
    }
    if (0 > hitbox->velocity__3i32F4.x__i32F4) {
        direction_of_movement |= DIRECTION__WEST;
    }
    if (0 < hitbox->velocity__3i32F4.y__i32F4) {
        direction_of_movement |= DIRECTION__NORTH;
    }
    if (0 > hitbox->velocity__3i32F4.y__i32F4) {
        direction_of_movement |= DIRECTION__SOUTH;
    }

    return direction_of_movement;
}

Direction__u8 get_tile_transition_direction_of__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb);

static void inline initialize_hitbox(
        Hitbox_AABB *hitbox,
        Quantity__u32 width, 
        Quantity__u32 height,
        Vector__3i32F4 position__3i32F4) {
    hitbox->width__quantity_32 = width;
    hitbox->height__quantity_u32 = height;
    hitbox->velocity__3i32F4.x__i32F4 = 0;
    hitbox->velocity__3i32F4.y__i32F4 = 0;
    hitbox->velocity__3i32F4.z__i32F4 = 0;
    set_hitbox__position_with__3i32F4(hitbox, 
            position__3i32F4);
}

///
/// TODO: really funny stuff happens when
///       we don't take vector as a pointer.
///       Why?
///
static void inline apply_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *vector) {
    hitbox->velocity__3i32F4.x__i32F4 += vector->x__i32F4;
    hitbox->velocity__3i32F4.y__i32F4 += vector->y__i32F4;
    hitbox->velocity__3i32F4.z__i32F4 += vector->z__i32F4;
}

static void inline apply_x_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 x__velocity) {
    hitbox->velocity__3i32F4.x__i32F4 += x__velocity;
}

static void inline apply_y_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 y__velocity) {
    hitbox->velocity__3i32F4.y__i32F4 += y__velocity;
}

static void inline apply_z_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 z__velocity) {
    hitbox->velocity__3i32F4.z__i32F4 += z__velocity;
}

static void inline set_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 velocity) {
    hitbox->velocity__3i32F4.x__i32F4 = velocity.x__i32F4;
    hitbox->velocity__3i32F4.y__i32F4 = velocity.y__i32F4;
    hitbox->velocity__3i32F4.z__i32F4 = velocity.z__i32F4;
}

static void inline set_x_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 x__velocity) {
    hitbox->velocity__3i32F4.x__i32F4 = x__velocity;
}

static void inline set_y_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 y__velocity) {
    hitbox->velocity__3i32F4.y__i32F4 = y__velocity;
}

static void inline set_z_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 z__velocity) {
    hitbox->velocity__3i32F4.z__i32F4 = z__velocity;
}

static bool inline is_vector_inside__hitbox(
        Vector__3i32F4 vector,
        Hitbox_AABB *p_hitbox) {
    Vector__3i32F4 aa, bb;
    get_points_aabb_from__hitbox(
            p_hitbox, 
            &aa, 
            &bb);
    return (
            vector.x__i32F4
            >= aa.x__i32F4
            && vector.x__i32F4
            <= bb.x__i32F4
            && vector.y__i32F4
            >= aa.y__i32F4
            && vector.y__i32F4
            <= bb.y__i32F4
            && vector.z__i32F4
            >= aa.z__i32F4
            && vector.z__i32F4
            <= aa.z__i32F4
            );
}

#endif
