#ifndef RENDER_ENTITY_H
#define RENDER_ENTITY_H

#include <defines.h>

static uint32_t inline get_animation_frame (
        uint32_t col, uint32_t row,
        uint32_t cols_per_row) {
    return
        col
        + (row * cols_per_row);
}

static uint32_t inline get_animation_frame_offset__for_cloth_armor(Entity *entity) {
    return
        get_animation_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset__for_iron_diamond_armor(Entity *entity) {
    return
        get_animation_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset__for_iron_amethyst_armor(Entity *entity) {
    return
        get_animation_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);

}

static uint32_t inline get_animation_frame_offset__for_gold_diamond_armor(Entity *entity) {
    return
        get_animation_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);

}

static uint32_t inline get_animation_frame_offset__for_gold_amethyst_armor(Entity *entity) {
    return
        get_animation_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);

}

static uint32_t inline get_animation_frame_offset__for_iron_armor(Entity *entity) {
    return
        get_animation_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);

}

static uint32_t inline get_animation_frame_offset__for_gold_armor(Entity *entity) {
    return
        get_animation_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD,
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);

}

uint32_t get_animation_frame_offset__for_direction(Direction direction,
        uint32_t cols_per_row);

static uint32_t inline get_animation_frame_offset__for_direction__of_humanoid_armored (
        Direction direction) {
    return 
        get_animation_frame_offset__for_direction(direction, 
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_ARMORED);
}

static uint32_t inline get_animation_frame_offset__for_direction__of_humanoid_unarmored (
        Direction direction) {
    return 
        get_animation_frame_offset__for_direction(direction, 
                SPRITE_FRAME_WIDTH__ENTITY_HUMANOID_UNARMORED);
}

uint32_t get_animation_frame_offset__for_armor(Entity *entity);

uint32_t get_animation_starting_frame__for_humanoid_entity(Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

uint32_t get_animation_starting_frame__for_entity(Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

void set_animation__of_entity(Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation);

void animate_entity__as_humanoid(Entity *entity);

void animate_entity(Entity *entity);

#endif
