#ifndef ANIMATE_SPRITE_H
#define ANIMATE_SPRITE_H

#include "defines_weak.h"
#include <defines.h>

static inline
bool is_animation__playing(
        Sprite_Wrapper sprite_wrapper,
        enum Sprite_Animation_Kind the_kind_of__animation) {
    return
        sprite_wrapper.the_kind_of_animation__this_sprite_has
        == the_kind_of__animation
        || sprite_wrapper.the_kind_of_animation__thats_upcomming
        == the_kind_of__animation
        ;
}

static inline 
bool is_animation__finished (
        Sprite_Wrapper sprite_wrapper) {
    return sprite_wrapper.frame 
        >= sprite_wrapper.frame__final;
}

static inline 
bool is_animation__finishing (
        Sprite_Wrapper sprite_wrapper) {
    return (sprite_wrapper.frame + 1)
        >= sprite_wrapper.frame__final;
}

static inline 
bool is_animation__transitionless(
        Sprite_Wrapper sprite_wrapper) {
    return sprite_wrapper.the_kind_of_animation__thats_upcomming
        == Sprite_Animation_Kind__None;
}

static inline
bool is_animation__not_running(
        Sprite_Wrapper sprite_wrapper) {
    return
        is_animation__finished(sprite_wrapper)
        && is_animation__transitionless(sprite_wrapper)
        ;
}

static inline 
bool is_animation__in_transition(
        Sprite_Wrapper sprite_wrapper) {
    return 
        is_animation__finished(sprite_wrapper)
        && sprite_wrapper.the_kind_of_animation__thats_upcomming
        != Sprite_Animation_Kind__None
        ;
}

static inline 
bool is_animation__transitioning_to(
        Sprite_Wrapper sprite_wrapper,
        enum Sprite_Animation_Kind animation_kind) {
    return is_animation__in_transition(sprite_wrapper)
        && sprite_wrapper.the_kind_of_animation__thats_upcomming
        == animation_kind
        ;
}

static inline 
uint32_t get_sprite_frame (
        uint32_t col, uint32_t row,
        uint32_t cols_per_row) {
    return
        col
        + (row * cols_per_row);
}

uint32_t get_animation_frame_offset_for__direction(
        Direction__u8 direction,
        uint32_t cols_per_row);

#endif
