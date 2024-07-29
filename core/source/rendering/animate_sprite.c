#include "defines_weak.h"
#include "timer.h"
#include <rendering/animate_sprite.h>
#include <entity/entity.h>
#include <debug/debug.h>

uint32_t get_animation_frame_offset_for__direction(
        Direction__u8 direction,
        uint32_t cols_per_row) {
    // TODO:    either make this work for any
    //          entity type, or move this
    //          to animate_humanoid.c
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

void set_animation_and__timer(
        Sprite_Wrapper *p_sprite_wrapper,
        enum Sprite_Animation_Kind the_kind_of__sprite_animation,
        Index__u8 frame__initial,
        Index__u8 frame__current,
        Index__u8 frame__final,
        Timer__u32 animation_timer__u32) {
    p_sprite_wrapper->the_kind_of_animation__this_sprite_has =
        the_kind_of__sprite_animation;
    p_sprite_wrapper->frame__initial =
        frame__initial;
    p_sprite_wrapper->frame__current =
        frame__current;
    p_sprite_wrapper->frame__final =
        frame__final;
    p_sprite_wrapper->animation_timer__u32 = animation_timer__u32;
}
