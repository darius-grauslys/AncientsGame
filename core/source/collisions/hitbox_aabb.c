#include <collisions/hitbox_aabb.h>

int32_t get_global_x_from__hitbox(
        Hitbox_AABB *hitbox) {
    return
    ((hitbox->x__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->x) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE);
}

int32_t get_global_y_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->y__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->y) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
}

int32_t get_global_z_from__hitbox(
        Hitbox_AABB *hitbox) {
    return 
    (((hitbox->z__chunk) << 
        ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
        + ((hitbox->z) >> 
            ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE));
}

void apply_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity) {

    int32_t dx, dy, dz;

    dx = ((hitbox->x + x__velocity) >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (hitbox->x >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    dy = ((hitbox->y + y__velocity) >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (hitbox->y >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    dz = ((hitbox->z + z__velocity) >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE)
        - (hitbox->z >> ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);

    hitbox->x += x__velocity
        - (dx << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    hitbox->y += y__velocity
        - (dy << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);
    hitbox->z += z__velocity
        - (dz << ENTITY_CHUNK_FRACTIONAL__BIT_SIZE);

    hitbox->x__chunk += dx;
    hitbox->y__chunk += dy;
    hitbox->z__chunk += dz;

    hitbox->x__global =
        get_global_x_from__hitbox(hitbox);
    hitbox->y__global =
        get_global_y_from__hitbox(hitbox);
    hitbox->z__global =
        get_global_z_from__hitbox(hitbox);
}

typedef struct Hitbox_Point_t {
    int32_t x, y;
} Hitbox_Point;

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
        hitbox->x__global
        + offset_half_width
        ;
    hitbox_point->y =
        hitbox->y__global
        + offset_half_length
        ;
}

bool is_this_hitbox__inside_this_hitbox(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
    Hitbox_Point aa__one;
    Hitbox_Point bb__one;

    init_hitbox_point(
            &aa__one, hitbox__one, 
            DIRECTION__NORTH_WEST);
    init_hitbox_point(
            &bb__one, hitbox__one, 
            DIRECTION__SOUTH_EAST);

    Hitbox_Point aa__two;
    Hitbox_Point bb__two;

    init_hitbox_point(
            &aa__two, hitbox__two, 
            DIRECTION__NORTH_WEST);
    init_hitbox_point(
            &bb__two, hitbox__two, 
            DIRECTION__SOUTH_EAST);

    bool is_aa__contained_along_x =
           aa__one.x > aa__two.x
        && aa__one.x < bb__two.x
        ;
    bool is_aa__contained_along_y =
           aa__one.y > aa__two.y
        && aa__one.y < bb__two.y
        ;
    if (is_aa__contained_along_x
        && is_aa__contained_along_y)
        return true;
    bool is_ab__contained_along_y =
           bb__one.y > aa__two.y
        && bb__one.y < bb__two.y
        ;
    if (is_aa__contained_along_x
        && is_ab__contained_along_y)
        return true;
    bool is_ba__contained_along_x =
           bb__one.x > aa__two.x
        && bb__one.x < bb__two.x
        ;
    if (is_ba__contained_along_x
        && is_aa__contained_along_y)
        return true;
    if (is_ba__contained_along_x
        && is_ab__contained_along_y)
        return true;

    // all corners checked, now do edges.

    bool is_aligned__x =
        aa__one.x == aa__two.x
        || bb__one.x == bb__two.x
        ;
    bool is_aligned__y =
        aa__one.y == aa__two.y
        || bb__one.y == bb__two.y
        ;

    if (is_aligned__x
        && (is_aa__contained_along_y
            || is_ab__contained_along_y))
        return true;
    if (is_aligned__y
        && (is_aa__contained_along_x
            || is_ba__contained_along_x))
        return true;
    return false;
}


bool is_hitboxes__overlapping(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two) {
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
    if (is_this_hitbox__inside_this_hitbox(
                hitbox__one, hitbox__two))
        return true;
    if (is_this_hitbox__inside_this_hitbox(
                hitbox__two, hitbox__one))
        return true;
    return false;
}
