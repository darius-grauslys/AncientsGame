#ifndef HUMANOID_ANIMATION_HANDLER_H
#define HUMANOID_ANIMATION_HANDLER_H

#include <defines.h>
#include <rendering/animate_sprite.h>

uint32_t get_animation_starting_frame_for__humanoid_entity(Entity *entity);

static void inline animate_humanoid__death(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Humanoid__Die;
}
static void inline animate_humanoid__use(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Humanoid__Use;
}
static void inline animate_humanoid__hurt(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Humanoid__Hurt;
}
static void inline animate_humanoid__walk(Entity *entity) {
    entity->sprite_wrapper.
        the_kind_of_animation__this_sprite_has =
        Sprite_Animation_Kind__Humanoid__Walk;
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

uint32_t get_animation_frame_offset_for__direction(Direction direction,
        uint32_t cols_per_row);

static uint32_t inline get_animation_frame_offset_for__direction__of_humanoid_armored (
        Direction direction) {
    return 
        get_animation_frame_offset_for__direction(direction, 
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset_for__direction__of_humanoid_unarmored (
        Direction direction) {
    return 
        get_animation_frame_offset_for__direction(direction, 
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_UNARMORED);
}

uint32_t get_animation_frame_offset_for__armor(Entity *entity);

void m_humanoid_animation_handler(Entity *entity, Timer timer);

#endif
