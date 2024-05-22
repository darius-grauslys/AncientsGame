#ifndef HITBOX_AABB_H
#define HITBOX_AABB_H

#include <defines.h>

Direction is_hitbox__colliding(
        Hitbox_AABB *hitbox__checking,
        Hitbox_AABB *hitbox__other);

void get_points_aabb_from__hitbox(
        Hitbox_AABB *hitbox,
        Hitbox_Point *aa,
        Hitbox_Point *bb);

static int32_t inline get_global_x_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->x__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->x + hitbox->x__velocity) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE);
}

static int32_t inline get_global_y_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->y__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->y + hitbox->y__velocity) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
}

static int32_t inline get_global_z_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->z__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->z + hitbox->z__velocity) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
}

static int32_t inline get_global_x_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->x__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->x) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE);
}

static int32_t inline get_global_y_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->y__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->y) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
}

static int32_t inline get_global_z_from__hitbox__without_velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->z__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->z) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
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
        int32_t x__global,
        int32_t y__global,
        int32_t z__global);

static Direction inline get_movement_direction_of__hitbox(
        Hitbox_AABB *hitbox) {
    Direction direction_of_movement =
        DIRECTION__NONE;
    if (0 < hitbox->x__velocity) {
        direction_of_movement |= DIRECTION__EAST;
    }
    if (0 > hitbox->x__velocity) {
        direction_of_movement |= DIRECTION__WEST;
    }
    if (0 < hitbox->y__velocity) {
        direction_of_movement |= DIRECTION__NORTH;
    }
    if (0 > hitbox->y__velocity) {
        direction_of_movement |= DIRECTION__SOUTH;
    }

    return direction_of_movement;
}

Direction get_tile_transition_direction_of__hitbox(
        Hitbox_AABB *hitbox,
        Hitbox_Point *aa,
        Hitbox_Point *bb);

static void inline init_hitbox(
        Hitbox_AABB *hitbox,
        int32_t width, int32_t length,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    hitbox->width = width;
    hitbox->length = length;
    hitbox->x__velocity = 0;
    hitbox->y__velocity = 0;
    hitbox->z__velocity = 0;
    set_hitbox__position(hitbox, 
            x__global, y__global, z__global);
}

static void inline apply_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity) {
    hitbox->x__velocity += x__velocity;
    hitbox->y__velocity += y__velocity;
    hitbox->z__velocity += z__velocity;
}

static void inline apply_x_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t x__velocity) {
    hitbox->x__velocity += x__velocity;
}

static void inline apply_y_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t y__velocity) {
    hitbox->y__velocity += y__velocity;
}

static void inline apply_z_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t z__velocity) {
    hitbox->z__velocity += z__velocity;
}

static void inline set_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity) {
    hitbox->x__velocity = x__velocity;
    hitbox->y__velocity = y__velocity;
    hitbox->z__velocity = z__velocity;
}

static void inline set_x_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t x__velocity) {
    hitbox->x__velocity = x__velocity;
}

static void inline set_y_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t y__velocity) {
    hitbox->y__velocity = y__velocity;
}

static void inline set_z_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t z__velocity) {
    hitbox->z__velocity = z__velocity;
}

#endif
