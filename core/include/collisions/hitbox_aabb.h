#ifndef HITBOX_AABB_H
#define HITBOX_AABB_H

#include <defines.h>

void init_hitbox_point_without__velocity(
        Hitbox_Point *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction corner_direction);

static void inline init_hitbox_point__aa_without__velocity(
        Hitbox_Point *aa,
        Hitbox_AABB *hitbox) {
    init_hitbox_point_without__velocity(
            aa, hitbox, 
            DIRECTION__SOUTH_WEST);
}

static void inline init_hitbox_point__bb_without__velocity(
        Hitbox_Point *bb,
        Hitbox_AABB *hitbox) {
    init_hitbox_point_without__velocity(
            bb, hitbox, 
            DIRECTION__NORTH_EAST);
}

void init_hitbox_point(Hitbox_Point *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction corner_direction);

static void inline init_hitbox_point__aa(
        Hitbox_Point *aa,
        Hitbox_AABB *hitbox) {
    init_hitbox_point(
            aa, hitbox, 
            DIRECTION__SOUTH_WEST);
}

static void inline init_hitbox_point__bb(
        Hitbox_Point *bb,
        Hitbox_AABB *hitbox) {
    init_hitbox_point(
            bb, hitbox, 
            DIRECTION__NORTH_EAST);
}

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

static int32_t inline get_global_x_from__hitbox_without__velocity(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->x__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->x) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE);
}

static int32_t inline get_global_y_from__hitbox_without__velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->y__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->y) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
}

static int32_t inline get_global_z_from__hitbox_without__velocity(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->z__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->z) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
}

// TODO: remove 32 magic number
//       the significance of 32 is that it's half the pixel width
//       of a chunk. We basically want it so that if you're
//       only 1 pixel into a chunk, you're on that chunk.
static int32_t inline get_aa__x__chunk_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
        (get_global_x_from__hitbox(hitbox) - (int32_t)hitbox->width / 2 + 32)
        >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE;
}

static int32_t inline get_aa__y__chunk_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
        (get_global_y_from__hitbox(hitbox) - (int32_t)hitbox->length / 2 + 32)
        >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE;
}

static int32_t inline get_bb__x__chunk_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
        (get_global_x_from__hitbox(hitbox) + (int32_t)hitbox->width / 2 + 32)
        >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE;
}

static int32_t inline get_bb__y__chunk_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
        (get_global_y_from__hitbox(hitbox) + (int32_t)hitbox->length / 2 + 32)
        >> ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE;
}

void commit_hitbox_velocity(
        Hitbox_AABB *hitbox);

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
    hitbox->x__velocity = x__velocity;
    hitbox->y__velocity = y__velocity;
    hitbox->z__velocity = z__velocity;
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

Direction is_hitbox__colliding(
        Hitbox_AABB *hitbox__checking,
        Hitbox_AABB *hitbox__other);

///
/// Use this, "using_points" inline invocation
/// if you plan on reusing some of the arguments
/// outside of a for loop.
///
static bool inline is_this_hitbox__inside_this_hitbox__using_points(
        Hitbox_Point *aa__one_moving,
        Hitbox_Point *bb__one_moving,
        Hitbox_Point *aa__two_still,
        Hitbox_Point *bb__two_still) {

    return 
        aa__one_moving->x < bb__two_still->x
        && bb__one_moving->x > aa__two_still->x
        && aa__one_moving->y < bb__two_still->y
        && bb__one_moving->y > aa__two_still->y;
}

static bool inline is_this_hitbox__inside_this_hitbox(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
    Hitbox_Point aa__one_moving;
    Hitbox_Point bb__one_moving;
    Hitbox_Point aa__two_still;
    Hitbox_Point bb__two_still;

    init_hitbox_point__aa(
            &aa__one_moving, 
            hitbox__one);
    init_hitbox_point__bb(
            &bb__one_moving, 
            hitbox__one);
    init_hitbox_point__aa_without__velocity(
            &aa__two_still, 
            hitbox__two);
    init_hitbox_point__bb_without__velocity(
            &bb__two_still, 
            hitbox__two);

    return is_this_hitbox__inside_this_hitbox__using_points(
            &bb__one_moving,
            &aa__one_moving,
            &bb__two_still,
            &aa__two_still);
}

///
/// Use this, "using_points" inline invocation
/// if you plan on reusing some of the arguments
/// outside of a for loop.
///
static bool inline is_this_hitbox_center__inside_this_hitbox__using_points(
        int32_t hitbox__one__x__global,
        int32_t hitbox__one__y__global,
        Hitbox_Point *hitbox__two__aa__still,
        Hitbox_Point *hitbox__two__bb__still) {

    return 
           hitbox__one__x__global < hitbox__two__bb__still->x
        && hitbox__one__x__global > hitbox__two__aa__still->x
        && hitbox__one__y__global < hitbox__two__bb__still->y
        && hitbox__one__y__global > hitbox__two__aa__still->y;
}

static bool inline is_this_hitbox_center__inside_this_hitbox(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
    Hitbox_Point hitbox__two__aa__still;
    Hitbox_Point hitbox__two__bb__still;

    init_hitbox_point__aa_without__velocity(
            &hitbox__two__aa__still, 
            hitbox__two);
    init_hitbox_point__bb_without__velocity(
            &hitbox__two__bb__still, 
            hitbox__two);

    return is_this_hitbox_center__inside_this_hitbox__using_points(
            get_global_x_from__hitbox(hitbox__one),
            get_global_y_from__hitbox(hitbox__two),
            &hitbox__two__aa__still,
            &hitbox__two__bb__still);
}

#endif
