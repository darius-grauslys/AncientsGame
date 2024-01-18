#ifndef HITBOX_AABB_H
#define HITBOX_AABB_H

#include <defines.h>

bool is_hitboxes__overlapping(
        Hitbox_AABB *hitbox__one,
        Hitbox_AABB *hitbox__two);

int32_t get_global_x_from__hitbox(
        Hitbox_AABB *hitbox);

int32_t get_global_y_from__hitbox(
        Hitbox_AABB *hitbox);

int32_t set_hitbox__position(
        Hitbox_AABB *hitbox,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global);

/// 
/// DO NOT CALL THIS! Unless you're a projectile.
/// This is called by apply_velocity_to__entity(...)
///
/// If you call this as a non-projectile entity
/// you can expect some very weird collision results.
///
void apply_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity);

#endif
