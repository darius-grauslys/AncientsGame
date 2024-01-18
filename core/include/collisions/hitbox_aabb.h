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

void apply_velocity_to__hitbox(
        Hitbox_AABB *hitbox,
        int32_t x__velocity,
        int32_t y__velocity,
        int32_t z__velocity);

#endif
