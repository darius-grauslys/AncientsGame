#ifndef ANIMATE_SPRITE_H
#define ANIMATE_SPRITE_H

#include <defines.h>

static bool inline is_animation__finished (
        Sprite_Wrapper sprite_wrapper) {
    return sprite_wrapper.frame 
        >= sprite_wrapper.frame__final;
}

static bool inline is_animation__exceeded (
        Sprite_Wrapper sprite_wrapper) {
    return sprite_wrapper.frame 
        >= sprite_wrapper.frame__final;
}

static bool inline is_animation__transitionless(
        Sprite_Wrapper sprite_wrapper) {
    return sprite_wrapper.the_kind_of_animation__thats_upcomming
        == Sprite_Animation_Kind__None;
}

static bool inline is_animation__in_transition(
        Sprite_Wrapper sprite_wrapper) {
    return 
        is_animation__finished(sprite_wrapper)
        && sprite_wrapper.the_kind_of_animation__thats_upcomming
        != Sprite_Animation_Kind__None
        ;
}

static bool inline is_animation__transitioning_to(
        Sprite_Wrapper sprite_wrapper,
        enum Sprite_Animation_Kind animation_kind) {
    return is_animation__in_transition(sprite_wrapper)
        && sprite_wrapper.the_kind_of_animation__thats_upcomming
        == animation_kind
        ;
}

static uint32_t inline get_sprite_frame (
        uint32_t col, uint32_t row,
        uint32_t cols_per_row) {
    return
        col
        + (row * cols_per_row);
}

static uint32_t inline get_animation_frame_offset_for__direction(
        Direction__u8 direction,
        uint32_t cols_per_row) {
    switch (direction) {
        default:
        case DIRECTION__EAST:
        case DIRECTION__WEST:
            return get_sprite_frame(
                    0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__SIDE_FACING,
                    cols_per_row);
        case DIRECTION__SOUTH:
            return get_sprite_frame(
                    0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__FORWARD_FACING,
                    cols_per_row);
        case DIRECTION__NORTH:
            return get_sprite_frame(
                    0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__BACK_FACING,
                    cols_per_row);
    }
}

///
/// Updates the sprite_wrapper.frame value.
///
void animate_sprite__humanoid(Entity *entity);

uint32_t get_start_frame__of_animation(
        Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

void set_sprite__animation(
        Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

#endif
