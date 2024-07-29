#ifndef ANIMATE_HUMANOID_H
#define ANIMATE_HUMANOID_H

#include "defines_weak.h"
#include "entity/entity.h"
#include <rendering/animate_entity.h>
#include <rendering/animate_sprite.h>
#include <defines.h>

uint32_t get_animation_starting_frame_for__humanoid_entity(Entity *entity);

static inline 
uint32_t get_animation_frame_offset_for__group(
        Index__u32 group_index) {
    Index__u32 frame__offset_u32 =
        SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
        * group_index 
        ;
    frame__offset_u32 =
        (frame__offset_u32 % 16)
        + ((frame__offset_u32 / 16)
                * 4 * 16)
        ;
    return frame__offset_u32;
}

uint32_t get_animation_frame_offset_for__direction(
        Direction__u8 direction,
        uint32_t cols_per_row);

static inline 
uint32_t get_animation_frame_offset_for__direction__of_humanoid_armored (
        Direction__u8 direction) {
    return 
        get_animation_frame_offset_for__direction(
                direction, 
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static inline 
uint32_t get_animation_frame_offset_for__direction__of_humanoid_unarmored (
        Direction__u8 direction) {
    return 
        get_animation_frame_offset_for__direction(
                direction, 
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_UNARMORED);
}

void set_animation_for__humanoid_with__timer_modification(
        Entity *p_humanoid,
        enum Sprite_Animation_Kind the_kind_of__animation,
        bool is_keeping__timer);

static inline
void set_animation_for__humanoid(
        Entity *p_humanoid,
        enum Sprite_Animation_Kind the_kind_of__animation) {
    if (is_animation_playing__this_kind_of__animation(
                get_p_sprite_wrapper_from__entity(p_humanoid), 
                the_kind_of__animation))
        return;
    set_animation_for__humanoid_with__timer_modification(
            p_humanoid, 
            the_kind_of__animation, 
            false);
}

static inline 
void animate_humanoid__death(Entity *p_humanoid) {
    set_animation_for__humanoid(
            p_humanoid, 
            Sprite_Animation_Kind__Humanoid__Die);
}

static inline 
void animate_humanoid__use(Entity *p_humanoid) {
    set_animation_for__humanoid(
            p_humanoid, 
            Sprite_Animation_Kind__Humanoid__Use);
}
static inline 
void animate_humanoid__hurt(Entity *p_humanoid) {
    set_animation_for__humanoid(
            p_humanoid, 
            Sprite_Animation_Kind__Humanoid__Hurt);
}
static inline 
void animate_humanoid__walk(Entity *p_humanoid) {
    set_animation_for__humanoid(
            p_humanoid, 
            Sprite_Animation_Kind__Humanoid__Walk);
}
static inline 
void animate_humanoid__idle(Entity *p_humanoid) {
    set_animation_for__humanoid(
            p_humanoid, 
            Sprite_Animation_Kind__Idle);
}

uint32_t get_animation_frame_offset_for__armor(Entity *entity);

Sprite_Frame_Index__u8 get_inital_sprite_frame_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind);

Sprite_Frame_Index__u8 get_final_sprite_frame_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind);

#endif
