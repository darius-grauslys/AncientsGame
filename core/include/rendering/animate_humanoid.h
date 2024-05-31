#ifndef ANIMATE_HUMANOID_H
#define ANIMATE_HUMANOID_H

#include <rendering/animate_entity.h>
#include <rendering/animate_sprite.h>
#include <defines.h>

uint32_t get_animation_starting_frame_for__humanoid_entity(Entity *entity);

static void inline animate_humanoid__death(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Die;
}
static void inline animate_humanoid__use(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Use;
}
static void inline animate_humanoid__hurt(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Hurt;
}
static void inline animate_humanoid__walk(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Humanoid__Walk;
}
static void inline animate_humanoid__idle(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__thats_upcomming =
        Sprite_Animation_Kind__Idle;
}

static uint32_t inline get_animation_frame_offset_for__cloth_armor(Entity *entity) {
    return
        get_sprite_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__iron_diamond_armor(Entity *entity) {
    return
        get_sprite_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__iron_amethyst_armor(Entity *entity) {
    return
        get_sprite_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__gold_diamond_armor(Entity *entity) {
    return
        get_sprite_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__gold_amethyst_armor(Entity *entity) {
    return
        get_sprite_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__iron_armor(Entity *entity) {
    return
        get_sprite_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__gold_armor(Entity *entity) {
    return
        get_sprite_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

uint32_t get_animation_frame_offset_for__direction(
        Direction__u8 direction,
        uint32_t cols_per_row);

static uint32_t inline get_animation_frame_offset_for__direction__of_humanoid_armored (
        Direction__u8 direction) {
    return 
        get_animation_frame_offset_for__direction(direction, 
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__direction__of_humanoid_unarmored (
        Direction__u8 direction) {
    return 
        get_animation_frame_offset_for__direction(direction, 
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

static void inline poll_humanoid_animation__transition(
        Entity *humanoid) {
    bool force = 
        humanoid->direction
        != humanoid->sprite_wrapper.direction;
    if (force) {
        humanoid->sprite_wrapper.direction =
            humanoid->direction;
        goto poll;
    }
    if (is_animation__exceeded(humanoid->sprite_wrapper) 
            && is_animation__transitionless(humanoid->sprite_wrapper)) {
        animate_humanoid__idle(humanoid);
    }
poll:
    poll_entity_animation__transition(
            humanoid, 
            f_get_inital_sprite_frame_for__humanoid_animation, 
            f_get_final_sprite_frame_for__humanoid_animation,
            force);
}

#endif
