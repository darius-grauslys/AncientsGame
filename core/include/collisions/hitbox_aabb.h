#ifndef HITBOX_AABB_H
#define HITBOX_AABB_H

#include <defines.h>
#include <vectors.h>
#include <world/chunk_vectors.h>

static Signed_Index__i32 inline get_x_i32_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_x_i32_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

static Signed_Index__i32 inline get_y_i32_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_y_i32_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

static Signed_Index__i32 inline get_z_i32_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_z_i32_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

static Signed_Index__i32 inline get_chunk_x_i32_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_chunk_x_i32_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

static Signed_Index__i32 inline get_chunk_y_i32_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_chunk_y_i32_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

static Signed_Index__i32 inline get_chunk_z_i32_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_chunk_z_i32_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

Direction__u8 is_hitbox__colliding(
        Hitbox_AABB *hitbox__checking,
        Hitbox_AABB *hitbox__other);

void get_aa_bb_as__vectors_3i32F4_from__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb);

void get_aa_bb_as__vectors_3i32_from__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32 *aa,
        Vector__3i32 *bb);

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

static bool inline is_vector_3i32F4_inside__hitbox(
        Vector__3i32F4 vector,
        Hitbox_AABB *p_hitbox) {
    Vector__3i32F4 aa, bb;
    get_aa_bb_as__vectors_3i32F4_from__hitbox(
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

static bool inline is_vector_3i32_inside__hitbox(
        Vector__3i32 vector,
        Hitbox_AABB *p_hitbox) {
    Vector__3i32 aa, bb;
    get_aa_bb_as__vectors_3i32_from__hitbox(
            p_hitbox, 
            &aa, 
            &bb);
    return (
            vector.x__i32
            >= aa.x__i32
            && vector.x__i32
            <= bb.x__i32
            && vector.y__i32
            >= aa.y__i32
            && vector.y__i32
            <= bb.y__i32
            && vector.z__i32
            >= aa.z__i32
            && vector.z__i32
            <= aa.z__i32
            );
}

#endif
