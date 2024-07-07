#include "defines.h"
#include "defines_weak.h"
#include "numerics.h"
#include "vectors.h"
#include <collisions/hitbox_aabb.h>
#include <debug/debug.h>

void set_hitbox__position_with__3i32F4(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 position__3i32F4) {
   hitbox->position__3i32F4 =
       position__3i32F4;
}

void set_hitbox__position_with__3i32(
        Hitbox_AABB *hitbox,
        Vector__3i32 position__3i32) {
    i32F4 x__global = position__3i32.x__i32;
    i32F4 y__global = position__3i32.y__i32;
    i32F4 z__global = position__3i32.z__i32;

    hitbox->position__3i32F4.x__i32F4 =
        x__global << FRACTIONAL_PERCISION_4__BIT_SIZE;
    hitbox->position__3i32F4.y__i32F4 =
        y__global << FRACTIONAL_PERCISION_4__BIT_SIZE;
    hitbox->position__3i32F4.z__i32F4 =
        z__global << FRACTIONAL_PERCISION_4__BIT_SIZE;
}

void commit_hitbox_velocity(
        Hitbox_AABB *hitbox) {

    add_p_vectors__3i32F4(
            &hitbox->position__3i32F4, 
            &hitbox->velocity__3i32F4);

    hitbox->velocity__3i32F4.x__i32F4 = 0;
    hitbox->velocity__3i32F4.y__i32F4 = 0;
    hitbox->velocity__3i32F4.z__i32F4 = 0;
}

void initialize_vector_3i32F4_as__aa_bb_without__velocity(
        Vector__3i32F4 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction) {

    Signed_Index__i32 offset_half_width = 
        (hitbox->width__quantity_u32 >> 1)
        << FRACTIONAL_PERCISION_4__BIT_SIZE;
    Signed_Index__i32 offset_half_height = 
        (hitbox->height__quantity_u32 >> 1)
        << FRACTIONAL_PERCISION_4__BIT_SIZE;
    switch (corner_direction) {
        default:
            // This should never be a problem...
            debug_error("Hitbox point initalization failed.");
            return;
        case DIRECTION__NORTH_EAST:
            break;
        case DIRECTION__NORTH_WEST:
            offset_half_width *= -1;
            break;
        case DIRECTION__SOUTH_EAST:
            offset_half_height *= -1;
            break;
        case DIRECTION__SOUTH_WEST:
            offset_half_width *= -1;
            offset_half_height *= -1;
            break;
    }

    hitbox_point->x__i32F4 =
        hitbox->position__3i32F4.x__i32F4
        + offset_half_width
        ;
    hitbox_point->y__i32F4 =
        hitbox->position__3i32F4.y__i32F4
        + offset_half_height
        ;
    hitbox_point->z__i32F4 = 0;
}

void initialize_vector_3i32F4_as__aa_bb(
        Vector__3i32F4 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction) {
    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            hitbox_point,
            hitbox,
            corner_direction);
    hitbox_point->x__i32F4 +=
        hitbox->velocity__3i32F4.x__i32F4;
    hitbox_point->y__i32F4 +=
        hitbox->velocity__3i32F4.y__i32F4;
}

void initialize_vector_3i32_as__aa_bb_without__velocity(
        Vector__3i32 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction) {

    Signed_Index__i32 offset_half_width = 
        hitbox->width__quantity_u32 >> 1;
    Signed_Index__i32 offset_half_height = 
        hitbox->height__quantity_u32 >> 1;
    switch (corner_direction) {
        default:
            // This should never be a problem...
            debug_error("Hitbox point initalization failed.");
            return;
        case DIRECTION__NORTH_EAST:
            break;
        case DIRECTION__NORTH_WEST:
            offset_half_width *= -1;
            break;
        case DIRECTION__SOUTH_EAST:
            offset_half_height *= -1;
            break;
        case DIRECTION__SOUTH_WEST:
            offset_half_width *= -1;
            offset_half_height *= -1;
            break;
    }

    hitbox_point->x__i32 =
        get_x_i32_from__hitbox(hitbox)
        + offset_half_width
        ;
    hitbox_point->y__i32 =
        get_y_i32_from__hitbox(hitbox)
        + offset_half_height
        ;
    hitbox_point->z__i32 = 0;
}

void initialize_vector_3i32_as__aa_bb(
        Vector__3i32 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction) {
    initialize_vector_3i32_as__aa_bb_without__velocity(
            hitbox_point,
            hitbox,
            corner_direction);
    hitbox_point->x__i32 +=
        get_x_i32_from__vector_3i32F4(hitbox->velocity__3i32F4);
    hitbox_point->y__i32 +=
        get_y_i32_from__vector_3i32F4(hitbox->velocity__3i32F4);
}

Direction__u8 get_tile_transition_direction_of__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb) {
    Direction__u8 direction_of_movement =
        get_movement_direction_of__hitbox(hitbox);
    Direction__u8 direction_of_transition =
        DIRECTION__NONE;

    Signed_Index__i32 x__tile_pos =
        (hitbox->position__3i32F4.x__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    Signed_Index__i32 y__tile_pos =
        (hitbox->position__3i32F4.y__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;

    initialize_vector_3i32F4_as__aa_bb(
            aa, hitbox, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32F4_as__aa_bb(
            bb, hitbox, 
            DIRECTION__NORTH_EAST);

    // TODO: consolidate bit manips
    Signed_Index__i32 x__aa_tile_pos =
        (aa->x__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    Signed_Index__i32 y__aa_tile_pos = 
        (aa->y__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    Signed_Index__i32 x__bb_tile_pos =
        (bb->x__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    Signed_Index__i32 y__bb_tile_pos = 
        (bb->y__i32F4 >> FRACTIONAL_PERCISION_4__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;

    if (direction_of_movement & DIRECTION__EAST
            && (x__bb_tile_pos > x__tile_pos)) {
        direction_of_transition |= DIRECTION__EAST;
    }
    if (direction_of_movement & DIRECTION__WEST
            && (x__aa_tile_pos < x__tile_pos)) {
        direction_of_transition |= DIRECTION__WEST;
    }
    if (direction_of_movement & DIRECTION__NORTH
            && (y__bb_tile_pos > y__tile_pos)) {
        direction_of_transition |= DIRECTION__NORTH;
    }
    if (direction_of_movement & DIRECTION__SOUTH
            && (y__aa_tile_pos < y__tile_pos)) {
        direction_of_transition |= DIRECTION__SOUTH;
    }

    return direction_of_transition;
}

bool is_this_hitbox__fully_inside_this_hitbox__without_velocity(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
    Vector__3i32F4 aa__one;
    Vector__3i32F4 bb__one;

    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &aa__one, hitbox__one, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &bb__one, hitbox__one, 
            DIRECTION__NORTH_EAST);

    Vector__3i32F4 aa__two;
    Vector__3i32F4 bb__two;

    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &aa__two, hitbox__two, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &bb__two, hitbox__two, 
            DIRECTION__NORTH_EAST);

    return
        aa__one.x__i32F4
        <= bb__two.x__i32F4
        && aa__one.x__i32F4
        >= aa__two.x__i32F4
        
        && aa__one.y__i32F4
        <= bb__two.y__i32F4
        && aa__one.y__i32F4
        >= aa__two.y__i32F4

        && bb__one.x__i32F4
        <= bb__two.x__i32F4
        && bb__one.x__i32F4
        >= aa__two.x__i32F4
        
        && bb__one.y__i32F4
        <= bb__two.y__i32F4
        && bb__one.y__i32F4
        >= aa__two.y__i32F4
        ;
}

Direction__u8 is_this_hitbox__inside_this_hitbox(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
    Vector__3i32F4 aa__one_moving;
    Vector__3i32F4 bb__one_moving;

    initialize_vector_3i32F4_as__aa_bb(
            &aa__one_moving, hitbox__one, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32F4_as__aa_bb(
            &bb__one_moving, hitbox__one, 
            DIRECTION__NORTH_EAST);

    Vector__3i32F4 aa__two;
    Vector__3i32F4 bb__two;

    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &aa__two, hitbox__two, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &bb__two, hitbox__two, 
            DIRECTION__NORTH_EAST);

    bool is_aa__contained_along_x =
           aa__one_moving.x__i32F4 > aa__two.x__i32F4
        && aa__one_moving.x__i32F4 < bb__two.x__i32F4
        ;
    bool is_aa__contained_along_y =
           aa__one_moving.y__i32F4 > aa__two.y__i32F4
        && aa__one_moving.y__i32F4 < bb__two.y__i32F4
        ;
    bool is_bb__contained_along_y =
           bb__one_moving.y__i32F4 > aa__two.y__i32F4
        && bb__one_moving.y__i32F4 < bb__two.y__i32F4
        ;
    bool is_bb__contained_along_x =
           bb__one_moving.x__i32F4 > aa__two.x__i32F4
        && bb__one_moving.x__i32F4 < bb__two.x__i32F4
        ;

    //// all corners acquired, now do edges.

    bool is_aligned__x =
        aa__one_moving.x__i32F4 == aa__two.x__i32F4
        || bb__one_moving.x__i32F4 == bb__two.x__i32F4
        ;
    bool is_aligned__y =
        aa__one_moving.y__i32F4 == aa__two.y__i32F4
        || bb__one_moving.y__i32F4 == bb__two.y__i32F4
        ;

    if (is_aa__contained_along_x && is_bb__contained_along_y)
        goto get_direction;
    if (is_aa__contained_along_y && is_bb__contained_along_x)
        goto get_direction;
    if (is_aa__contained_along_x && is_aa__contained_along_y)
        goto get_direction;
    if (is_bb__contained_along_x && is_bb__contained_along_y)
        goto get_direction;
    if (is_aligned__x
        && (is_aa__contained_along_y
            || is_bb__contained_along_y))
        goto get_direction;
    if (is_aligned__y
        && (is_aa__contained_along_x
            || is_bb__contained_along_x))
        goto get_direction;
    if (is_aligned__x && is_aligned__y)
        goto get_direction;
    return DIRECTION__NONE;

get_direction:
    Vector__3i32F4 aa__one_still;
    Vector__3i32F4 bb__one_still;
    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &aa__one_still, hitbox__one, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32F4_as__aa_bb_without__velocity(
            &bb__one_still, hitbox__one, 
            DIRECTION__NORTH_EAST);

    bool is_still_aa__contained_along_x =
           aa__one_still.x__i32F4 > aa__two.x__i32F4
        && aa__one_still.x__i32F4 < bb__two.x__i32F4
        ;
    bool is_still_aa__contained_along_y =
           aa__one_still.y__i32F4 > aa__two.y__i32F4
        && aa__one_still.y__i32F4 < bb__two.y__i32F4
        ;
    bool is_still_bb__contained_along_y =
           bb__one_still.y__i32F4 > aa__two.y__i32F4
        && bb__one_still.y__i32F4 < bb__two.y__i32F4
        ;
    bool is_still_bb__contained_along_x =
           bb__one_still.x__i32F4 > aa__two.x__i32F4
        && bb__one_still.x__i32F4 < bb__two.x__i32F4
        ;

    //// all corners acquired, now do edges.

    bool is_still_aligned__x =
        aa__one_still.x__i32F4 == aa__two.x__i32F4
        || bb__one_still.x__i32F4 == bb__two.x__i32F4
        ;
    // printf("state alg_x: %b\n",
    //        is_still_aligned__x);
    bool is_still_aligned__y =
        aa__one_still.y__i32F4 == aa__two.y__i32F4
        || bb__one_still.y__i32F4 == bb__two.y__i32F4
        ;

    Direction__u8 direction_of_movement =
        get_movement_direction_of__hitbox(hitbox__one);
    Direction__u8 direction_of_collision = DIRECTION__NONE;

    if (direction_of_movement & DIRECTION__EAST) {
        if (is_still_aa__contained_along_y 
                || is_still_bb__contained_along_y
                || is_still_aligned__y)
            direction_of_collision |= DIRECTION__EAST;
    }
    if (direction_of_movement & DIRECTION__WEST) {
        if (is_still_aa__contained_along_y 
                || is_still_bb__contained_along_y
                || is_still_aligned__y)
            direction_of_collision |= DIRECTION__WEST;
    }
    if (direction_of_movement & DIRECTION__NORTH) {
        if (is_still_aa__contained_along_x
                || is_still_bb__contained_along_x
                || is_still_aligned__x)
            direction_of_collision |= DIRECTION__NORTH;
    }
    if (direction_of_movement & DIRECTION__SOUTH) {
        if (is_still_aa__contained_along_x
                || is_still_bb__contained_along_x
                || is_still_aligned__x)
            direction_of_collision |= DIRECTION__SOUTH;
    }

    return direction_of_collision;
}


Direction__u8 is_hitbox__colliding(
        Hitbox_AABB *hitbox__checking,
        Hitbox_AABB *hitbox__other) {
    // It is not enough to check if a corner
    // is in a given hitbox.
    //
    // Take for example, a situation where two
    // hitboxes are equal in dimensions, and they
    // collide into each other on one face perfectly.
    // In such a situation neither hitbox will have a
    // corner in the other, but they will each have
    // an edge in the other.
    //
    // Hitbox collision is therefore not about checking
    // if corners are inside another hitbox, but
    // rather checking if edges are.
    return is_this_hitbox__inside_this_hitbox(
                hitbox__checking, hitbox__other);
}

void get_aa_bb_as__vectors_3i32F4_from__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb) {
    initialize_vector_3i32F4_as__aa_bb(
            aa, 
            hitbox, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32F4_as__aa_bb(
            bb, 
            hitbox, 
            DIRECTION__NORTH_EAST);
}

void get_aa_bb_as__vectors_3i32_from__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32 *aa,
        Vector__3i32 *bb) {
    initialize_vector_3i32_as__aa_bb(
            aa, 
            hitbox, 
            DIRECTION__SOUTH_WEST);
    initialize_vector_3i32_as__aa_bb(
            bb, 
            hitbox, 
            DIRECTION__NORTH_EAST);
}

void clamp_p_vector_3i32_to__hitbox(
        Hitbox_AABB *p_hitbox, 
        Vector__3i32 *p_position__3i32) {
    Vector__3i32 aa, bb;
    get_aa_bb_as__vectors_3i32_from__hitbox(
            p_hitbox, 
            &aa, 
            &bb);
    clamp__p_i32(
            get_p_x_i32_from__p_vector_3i32(p_position__3i32), 
            aa.x__i32, 
            bb.x__i32);
    clamp__p_i32(
            get_p_y_i32_from__p_vector_3i32(p_position__3i32), 
            aa.y__i32, 
            bb.y__i32);
    clamp__p_i32(
            get_p_z_i32_from__p_vector_3i32(p_position__3i32), 
            aa.z__i32, 
            bb.z__i32);
}
