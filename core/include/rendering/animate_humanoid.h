#ifndef ANIMATE_HUMANOID_H
#define ANIMATE_HUMANOID_H

#include "defines_weak.h"
#include <rendering/animate_entity.h>
#include <rendering/animate_sprite.h>
#include <defines.h>

uint32_t get_animation_starting_frame_for__humanoid_entity(Entity *entity);

static inline 
void animate_humanoid__death(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Die;
}
static inline 
void animate_humanoid__use(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Use;
}
static inline 
void animate_humanoid__hurt(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Hurt;
}
static inline 
void animate_humanoid__walk(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Walk;
}
static inline 
void animate_humanoid__idle(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Idle;
}

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

uint32_t get_animation_frame_offset_for__armor(Entity *entity);

Sprite_Frame_Index__u8 f_get_inital_sprite_frame_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind);

Sprite_Frame_Index__u8 f_get_final_sprite_frame_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind);

Quantity__u32 f_get_animation_speed_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind);

Quantity__u32 f_get_animation_duration_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind);

void poll_humanoid_animation__transition(
        Entity *humanoid);

#endif
