#ifndef HITBOX_AABB_H
#define HITBOX_AABB_H

#include <defines.h>

Direction is_hitbox__colliding(
        Hitbox_AABB *hitbox__checking,
        Hitbox_AABB *hitbox__other);

void get_points_aabb_from__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb);

static Signed_Index__i32 inline get_global_x_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->x__chunk__signed_index_i32) 
     << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->x__i32F4 + hitbox->x__velocity__i32F4) 
                >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        ;
}

static Signed_Index__i32 inline get_global_y_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->y__chunk__signed_index_i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->y__i32F4 + hitbox->y__velocity__i32F4) 
            >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE))
    ;
}

static Signed_Index__i32 inline get_global_z_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->z__chunk__signed_index_i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->z__i32F4 + hitbox->z__velocity__i32F4) 
            >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE))
    ;
}

static Signed_Index__i32 inline get_global_x_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->x__chunk__signed_index_i32) 
     << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->x__i32F4) 
                >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        ;
}

static Signed_Index__i32 inline get_global_y_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->y__chunk__signed_index_i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->y__i32F4) 
            >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE))
    ;
}

static Signed_Index__i32 inline get_global_z_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->z__chunk__signed_index_i32) 
      << ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->z__i32F4) 
            >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE))
    ;
}

void commit_hitbox_velocity(
        Hitbox_AABB *hitbox);

///
/// BE CAREFUL!!!
/// Whenever you call this, you need to
/// make sure the entity's record in the collision_manager
/// is updated!!!
///
void set_hitbox__position(
        Hitbox_AABB *hitbox,
        Signed_Index__i32 x__global,
        Signed_Index__i32 y__global,
        Signed_Index__i32 z__global);

static Direction__u8 inline get_movement_direction_of__hitbox(
        Hitbox_AABB *hitbox) {
    Direction__u8 direction_of_movement =
        DIRECTION__NONE;
    if (0 < hitbox->x__velocity__i32F4) {
        direction_of_movement |= DIRECTION__EAST;
    }
    if (0 > hitbox->x__velocity__i32F4) {
        direction_of_movement |= DIRECTION__WEST;
    }
    if (0 < hitbox->y__velocity__i32F4) {
        direction_of_movement |= DIRECTION__NORTH;
    }
    if (0 > hitbox->y__velocity__i32F4) {
        direction_of_movement |= DIRECTION__SOUTH;
    }

    return direction_of_movement;
}

Direction get_tile_transition_direction_of__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb);

static void inline init_hitbox(
        Hitbox_AABB *hitbox,
        Quantity__u32 width, 
        Quantity__u32 height,
        Signed_Index__i32 x__global,
        Signed_Index__i32 y__global,
        Signed_Index__i32 z__global) {
    hitbox->width__quantity_32 = width;
    hitbox->height__quantity_u32 = height;
    hitbox->x__velocity__i32F4 = 0;
    hitbox->y__velocity__i32F4 = 0;
    hitbox->z__velocity__i32F4 = 0;
    set_hitbox__position(hitbox, 
            x__global, y__global, z__global);
}

static void inline apply_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 x__velocity,
        i32F4 y__velocity,
        i32F4 z__velocity) {
    hitbox->x__velocity__i32F4 += x__velocity;
    hitbox->y__velocity__i32F4 += y__velocity;
    hitbox->z__velocity__i32F4 += z__velocity;
}

static void inline apply_x_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 x__velocity) {
    hitbox->x__velocity__i32F4 += x__velocity;
}

static void inline apply_y_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 y__velocity) {
    hitbox->y__velocity__i32F4 += y__velocity;
}

static void inline apply_z_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 z__velocity) {
    hitbox->z__velocity__i32F4 += z__velocity;
}

static void inline set_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 x__velocity,
        i32F4 y__velocity,
        i32F4 z__velocity) {
    hitbox->x__velocity__i32F4 = x__velocity;
    hitbox->y__velocity__i32F4 = y__velocity;
    hitbox->z__velocity__i32F4 = z__velocity;
}

static void inline set_x_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 x__velocity) {
    hitbox->x__velocity__i32F4 = x__velocity;
}

static void inline set_y_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 y__velocity) {
    hitbox->y__velocity__i32F4 = y__velocity;
}

static void inline set_z_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        i32F4 z__velocity) {
    hitbox->z__velocity__i32F4 = z__velocity;
}

#endif
