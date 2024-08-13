#ifndef HITBOX_AABB_H
#define HITBOX_AABB_H

#include <defines.h>
#include <vectors.h>
#include <world/chunk_vectors.h>

static i32F4 inline get_x_i32F4_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_x_i32F4_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

static i32F4 inline get_y_i32F4_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_y_i32F4_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

static i32F4 inline get_z_i32F4_from__hitbox(
        Hitbox_AABB *p_hitbox) {
    return get_z_i32F4_from__vector_3i32F4(p_hitbox->position__3i32F4);
}

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

Direction__u8 get_movement_direction_of__hitbox(
        Hitbox_AABB *hitbox);

Direction__u8 get_tile_transition_direction_of__hitbox(
        Hitbox_AABB *hitbox,
        Vector__3i32F4 *aa,
        Vector__3i32F4 *bb);

void initialize_vector_3i32F4_as__aa_bb_without__velocity(
        Vector__3i32F4 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction);

void initialize_vector_3i32F4_as__aa_bb(
        Vector__3i32F4 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction);

void initialize_vector_3i32_as__aa_bb_without__velocity(
        Vector__3i32 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction);

void initialize_vector_3i32_as__aa_bb(
        Vector__3i32 *hitbox_point,
        Hitbox_AABB *hitbox,
        Direction__u8 corner_direction);

void clamp_p_vector_3i32_to__hitbox(
        Hitbox_AABB *p_hitbox, 
        Vector__3i32 *p_position__3i32);

void initialize_hitbox(
        Hitbox_AABB *hitbox,
        Quantity__u32 width, 
        Quantity__u32 height,
        Vector__3i32F4 position__3i32F4);

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

///
/// NOTE: Only checks the corners of hitbox__one
/// against hitbox__two. In otherwords, if hitbox__two
/// is fully within hitbox__one, this will return
/// DIRECTION__NONE.
///
Direction__u8 is_this_hitbox__overlapping_this_hitbox(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two);

bool is_vector_3i32F4_inside__hitbox(
        Vector__3i32F4 vector,
        Hitbox_AABB *p_hitbox);

bool is_vector_3i32_inside__hitbox(
        Vector__3i32 vector,
        Hitbox_AABB *p_hitbox);

bool is_this_hitbox__fully_inside_this_hitbox__without_velocity(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two);

#endif
