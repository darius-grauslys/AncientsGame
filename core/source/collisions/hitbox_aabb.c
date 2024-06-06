#include "defines.h"
#include "vectors.h"
#include <collisions/hitbox_aabb.h>
#include <debug/debug.h>

static void inline normalize_hitbox__position_plus_velocity_with__chunk_space(
        Hitbox_AABB *p_hitbox,
        Chunk_Vector__3i32 d_chunk_vector) {
    p_hitbox->position__3i32F4.x__i32F4 += p_hitbox->velocity__3i32F4.x__i32F4
        - (d_chunk_vector.x__i32 << ENTITY_CHUNK_LOCAL_SPACE_FRACTIONAL__BIT_SIZE);
    p_hitbox->position__3i32F4.y__i32F4 += p_hitbox->velocity__3i32F4.y__i32F4
        - (d_chunk_vector.y__i32 << ENTITY_CHUNK_LOCAL_SPACE_FRACTIONAL__BIT_SIZE);
    p_hitbox->position__3i32F4.z__i32F4 += p_hitbox->velocity__3i32F4.z__i32F4
        - (d_chunk_vector.z__i32 << ENTITY_CHUNK_LOCAL_SPACE_FRACTIONAL__BIT_SIZE);
}

void set_hitbox__position_with__3i32F4(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 position__3i32F4) {
    i32F4 x__global = position__3i32F4.x__i32F4;
    i32F4 y__global = position__3i32F4.y__i32F4;
    i32F4 z__global = position__3i32F4.z__i32F4;

    hitbox->chunk_index__3i32 =
        vector_3i32F4_to__chunk_vector_3i32(position__3i32F4);

    hitbox->position__3i32F4.x__i32F4 = x__global
        % (8 << 7)
        ;
    hitbox->position__3i32F4.y__i32F4 = y__global
        % (8 << 7)
        ;
    hitbox->position__3i32F4.z__i32F4 = z__global
        % (8 << 7)
        ;
    return;
    hitbox->position__3i32F4.x__i32F4 =
        (x__global) 
        % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1);
    hitbox->position__3i32F4.y__i32F4 =
        (y__global) 
        % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1);
    hitbox->position__3i32F4.z__i32F4 =
        (z__global) 
        % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1);
}

void set_hitbox__position_with__3i32(
        Hitbox_AABB *hitbox,
        Vector__3i32 position__3i32) {
    i32F4 x__global = position__3i32.x__i32;
    i32F4 y__global = position__3i32.y__i32;
    i32F4 z__global = position__3i32.z__i32;

    hitbox->chunk_index__3i32 =
        vector_3i32_to__chunk_vector_3i32(position__3i32);

    hitbox->position__3i32F4.x__i32F4 =
        (x__global % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1));
    hitbox->position__3i32F4.y__i32F4 =
        (y__global % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1));
    hitbox->position__3i32F4.z__i32F4 =
        (z__global % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1));
}

void commit_hitbox_velocity(
        Hitbox_AABB *hitbox) {

    Vector__3i32F4 velocity_commit_vector =
        add_vectors__3i32F4(
                hitbox->position__3i32F4, 
                hitbox->velocity__3i32F4);
    Chunk_Vector__3i32 velocity_commit___chunk_vector =
        vector_3i32F4_to__chunk_vector_3i32(
                velocity_commit_vector);
    Chunk_Vector__3i32 hitbox_position__chunk_vector =
        vector_3i32F4_to__chunk_vector_3i32(
                hitbox->position__3i32F4);
    Chunk_Vector__3i32 d_chunk_vector =
        subtract_vectors__3i32(
                velocity_commit___chunk_vector, 
                hitbox_position__chunk_vector);

    normalize_hitbox__position_plus_velocity_with__chunk_space(
        hitbox, 
        d_chunk_vector);

    hitbox->velocity__3i32F4.x__i32F4 = 0;
    hitbox->velocity__3i32F4.y__i32F4 = 0;
    hitbox->velocity__3i32F4.z__i32F4 = 0;

    add_p_vectors__3i32(
            &hitbox->chunk_index__3i32, 
            &d_chunk_vector);
}

void initialize_hitbox_point__without_velocity(Vector__3i32F4 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction) {

    Signed_Index__i32 offset_half_width = hitbox->width__quantity_32 / 2;
    Signed_Index__i32 offset_half_height = hitbox->height__quantity_u32 / 2;
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
        get_global_x_from__hitbox__without_velocity(hitbox)
        + offset_half_width
        ;
    hitbox_point->y__i32F4 =
        get_global_y_from__hitbox__without_velocity(hitbox)
        + offset_half_height
        ;
}

void initialize_hitbox_point(Vector__3i32F4 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction) {

    Signed_Index__i32 offset_half_width = hitbox->width__quantity_32 / 2;
    Signed_Index__i32 offset_half_height = hitbox->height__quantity_u32 / 2;
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
        get_global_x_from__hitbox(hitbox)
        + offset_half_width
        ;
    hitbox_point->y__i32F4 =
        get_global_y_from__hitbox(hitbox)
        + offset_half_height
        ;
    //TODO: 3d
    hitbox_point->z__i32F4 = 0;
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

    initialize_hitbox_point(
            aa, hitbox, 
            DIRECTION__SOUTH_WEST);
    initialize_hitbox_point(
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

Direction__u8 is_this_hitbox__inside_this_hitbox(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
    Vector__3i32F4 aa__one_moving;
    Vector__3i32F4 bb__one_moving;

    initialize_hitbox_point(
            &aa__one_moving, hitbox__one, 
            DIRECTION__SOUTH_WEST);
    initialize_hitbox_point(
            &bb__one_moving, hitbox__one, 
            DIRECTION__NORTH_EAST);

    Vector__3i32F4 aa__two;
    Vector__3i32F4 bb__two;

    initialize_hitbox_point__without_velocity(
            &aa__two, hitbox__two, 
            DIRECTION__SOUTH_WEST);
    initialize_hitbox_point__without_velocity(
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
    initialize_hitbox_point__without_velocity(
            &aa__one_still, hitbox__one, 
            DIRECTION__SOUTH_WEST);
    initialize_hitbox_point__without_velocity(
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

void get_points_aabb_from__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb) {
    initialize_hitbox_point(aa, hitbox, DIRECTION__SOUTH_WEST);
    initialize_hitbox_point(bb, hitbox, DIRECTION__NORTH_EAST);
}
