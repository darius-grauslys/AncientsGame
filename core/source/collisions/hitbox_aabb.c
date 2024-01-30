#include <collisions/hitbox_aabb.h>
#include <debug/debug.h>

void set_hitbox__position(
        Hitbox_AABB *hitbox,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    hitbox->x__chunk = 
        x__global / (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1);
    hitbox->y__chunk = 
        y__global / (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1);
    hitbox->z__chunk = 
        z__global / (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1);

    hitbox->x =
        (x__global % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1))
        << ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE;
    hitbox->y =
        (y__global % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1))
        << ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE;
    hitbox->z =
        (z__global % (ENTITY_CHUNK_LOCAL_SPACE__BIT_MASK + 1)
        << ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE);
}

void commit_hitbox_velocity(
        Hitbox_AABB *hitbox) {

    int32_t dx, dy, dz;

    dx = ((hitbox->x + hitbox->x__velocity) 
            >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (hitbox->x >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    dy = ((hitbox->y + hitbox->y__velocity) 
            >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (hitbox->y >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    dz = ((hitbox->z + hitbox->z__velocity) 
            >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (hitbox->z >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);

    hitbox->x += hitbox->x__velocity
        - (dx << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    hitbox->y += hitbox->y__velocity
        - (dy << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    hitbox->z += hitbox->z__velocity
        - (dz << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);

    hitbox->x__velocity = 0;
    hitbox->y__velocity = 0;
    hitbox->z__velocity = 0;

    hitbox->x__chunk += dx;
    hitbox->y__chunk += dy;
    hitbox->z__chunk += dz;
}

void init_hitbox_point__without_velocity(Hitbox_Point *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction corner_direction) {

    int32_t offset_half_width = hitbox->width / 2;
    int32_t offset_half_length = hitbox->length / 2;
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
            offset_half_length *= -1;
            break;
        case DIRECTION__SOUTH_WEST:
            offset_half_width *= -1;
            offset_half_length *= -1;
            break;
    }

    hitbox_point->x =
        get_global_x_from__hitbox__without_velocity(hitbox)
        + offset_half_width
        ;
    hitbox_point->y =
        get_global_y_from__hitbox__without_velocity(hitbox)
        + offset_half_length
        ;
}

void init_hitbox_point(Hitbox_Point *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction corner_direction) {

    int32_t offset_half_width = hitbox->width / 2;
    int32_t offset_half_length = hitbox->length / 2;
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
            offset_half_length *= -1;
            break;
        case DIRECTION__SOUTH_WEST:
            offset_half_width *= -1;
            offset_half_length *= -1;
            break;
    }

    hitbox_point->x =
        get_global_x_from__hitbox(hitbox)
        + offset_half_width
        ;
    hitbox_point->y =
        get_global_y_from__hitbox(hitbox)
        + offset_half_length
        ;
}

Direction get_tile_transition_direction_of__hitbox(
        Hitbox_AABB *hitbox,
        Hitbox_Point *aa,
        Hitbox_Point *bb) {
    Direction direction_of_movement =
        get_movement_direction_of__hitbox(hitbox);
    Direction direction_of_transition =
        DIRECTION__NONE;

    int32_t x__tile_pos =
        (hitbox->x >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    int32_t y__tile_pos =
        (hitbox->y >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;

    init_hitbox_point(
            aa, hitbox, 
            DIRECTION__SOUTH_WEST);
    init_hitbox_point(
            bb, hitbox, 
            DIRECTION__NORTH_EAST);

    int32_t x__aa_tile_pos =
        (aa->x >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    int32_t y__aa_tile_pos = 
        (aa->y >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    int32_t x__bb_tile_pos =
        (bb->x >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;
    int32_t y__bb_tile_pos = 
        (bb->y >> ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)
        >> TILE_PIXEL_WIDTH__BIT_SIZE
        ;

    if (direction_of_movement & DIRECTION__EAST
            && (x__bb_tile_pos > x__tile_pos)) {
        direction_of_transition |= DIRECTION__EAST;
    }
    if (direction_of_movement & DIRECTION__WEST
            && (x__bb_tile_pos > x__tile_pos)) {
        direction_of_transition |= DIRECTION__WEST;
    }
    if (direction_of_movement & DIRECTION__NORTH
            && (x__bb_tile_pos > x__tile_pos)) {
        direction_of_transition |= DIRECTION__NORTH;
    }
    if (direction_of_movement & DIRECTION__SOUTH
            && (x__bb_tile_pos > x__tile_pos)) {
        direction_of_transition |= DIRECTION__SOUTH;
    }

    return direction_of_transition;
}

Direction is_this_hitbox__inside_this_hitbox(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
    Hitbox_Point aa__one_moving;
    Hitbox_Point bb__one_moving;

    init_hitbox_point(
            &aa__one_moving, hitbox__one, 
            DIRECTION__SOUTH_WEST);
    init_hitbox_point(
            &bb__one_moving, hitbox__one, 
            DIRECTION__NORTH_EAST);

    // printf("\npnt_aa_one: %d, %d\n", 
    //         aa__one.x, aa__one.y);
    // printf("pnt_bb_one: %d, %d\n", 
    //         bb__one.x, bb__one.y);

    Hitbox_Point aa__two;
    Hitbox_Point bb__two;

    init_hitbox_point__without_velocity(
            &aa__two, hitbox__two, 
            DIRECTION__SOUTH_WEST);
    init_hitbox_point__without_velocity(
            &bb__two, hitbox__two, 
            DIRECTION__NORTH_EAST);

    // printf("pnt_aa_two: %d, %d\n", 
    //         aa__two.x, aa__two.y);
    // printf("pnt_bb_two: %d, %d\n", 
    //         bb__two.x, bb__two.y);

    bool is_aa__contained_along_x =
           aa__one_moving.x > aa__two.x
        && aa__one_moving.x < bb__two.x
        ;
    // printf("state aa_x: %b\n",
    //         is_aa__contained_along_x);
    bool is_aa__contained_along_y =
           aa__one_moving.y > aa__two.y
        && aa__one_moving.y < bb__two.y
        ;
    // printf("state aa_y: %b\n",
    //         is_aa__contained_along_y);
    bool is_bb__contained_along_y =
           bb__one_moving.y > aa__two.y
        && bb__one_moving.y < bb__two.y
        ;
    // printf("state ab_y: %b\n",
    //         is_ab__contained_along_y);
    bool is_bb__contained_along_x =
           bb__one_moving.x > aa__two.x
        && bb__one_moving.x < bb__two.x
        ;
    // printf("state bb_x: %b\n",
    //         is_ba__contained_along_x);

    //// all corners acquired, now do edges.

    bool is_aligned__x =
        aa__one_moving.x == aa__two.x
        || bb__one_moving.x == bb__two.x
        ;
    // printf("state alg_x: %b\n",
    //        is_aligned__x);
    bool is_aligned__y =
        aa__one_moving.y == aa__two.y
        || bb__one_moving.y == bb__two.y
        ;
    // printf("state alg_y: %b\n",
    //        is_aligned__x);

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
    Hitbox_Point aa__one_still;
    Hitbox_Point bb__one_still;
    init_hitbox_point__without_velocity(
            &aa__one_still, hitbox__one, 
            DIRECTION__SOUTH_WEST);
    init_hitbox_point__without_velocity(
            &bb__one_still, hitbox__one, 
            DIRECTION__NORTH_EAST);

    bool is_still_aa__contained_along_x =
           aa__one_still.x > aa__two.x
        && aa__one_still.x < bb__two.x
        ;
    bool is_still_aa__contained_along_y =
           aa__one_still.y > aa__two.y
        && aa__one_still.y < bb__two.y
        ;
    bool is_still_bb__contained_along_y =
           bb__one_still.y > aa__two.y
        && bb__one_still.y < bb__two.y
        ;
    bool is_still_bb__contained_along_x =
           bb__one_still.x > aa__two.x
        && bb__one_still.x < bb__two.x
        ;

    //// all corners acquired, now do edges.

    bool is_still_aligned__x =
        aa__one_still.x == aa__two.x
        || bb__one_still.x == bb__two.x
        ;
    // printf("state alg_x: %b\n",
    //        is_still_aligned__x);
    bool is_still_aligned__y =
        aa__one_still.y == aa__two.y
        || bb__one_still.y == bb__two.y
        ;

    Direction direction_of_movement =
        get_movement_direction_of__hitbox(hitbox__one);
    Direction direction_of_collision = DIRECTION__NONE;

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


Direction is_hitbox__colliding(
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
