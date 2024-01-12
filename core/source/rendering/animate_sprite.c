#include <rendering/animate_sprite.h>
#include <entity/entity.h>
#include <debug/debug.h>

uint32_t get_frame(uint32_t col, uint32_t row) {
    return
        col
        + (row * (SPRITE_FRAME_COL__ENTITY_HUMANOID__LAST_COL+1));
}

uint32_t get_frame_offset__for_direction(Entity *entity) {
    switch (entity->sprite_wrapper.direction) {
        default:
        case Direction__East:
        case Direction__West:
            return get_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__SIDE_FACING);
        case Direction__South:
            return get_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__FORWARD_FACING);
        case Direction__North:
            return get_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__BACK_FACING);
    }
}

uint32_t get_frame_offset__for_cloth_armor(Entity *entity) {
    return
        get_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH);
}

uint32_t get_frame_offset__for_iron_diamond_armor(Entity *entity) {
    return
        get_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_DIAMOND);
}

uint32_t get_frame_offset__for_iron_amethyst_armor(Entity *entity) {
    return
        get_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON_AMETHYST);
}

uint32_t get_frame_offset__for_gold_diamond_armor(Entity *entity) {
    return
        get_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_DIAMOND);
}

uint32_t get_frame_offset__for_gold_amethyst_armor(Entity *entity) {
    return
        get_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD_AMETHYST);
}

uint32_t get_frame_offset__for_iron_armor(Entity *entity) {
    return
        get_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON);
}

uint32_t get_frame_offset__for_gold_armor(Entity *entity) {
    return
        get_frame(
                SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_COL_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD,
                SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                * SPRITE_FRAME_ROW_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD);
}

uint32_t get_frame_offset__from_entity_armor(Entity *entity) {
    switch (entity->armor_properties.the_kind_of_armor__this_armor_is) {
        default:
        case Entity_Armor_Kind__None:
            return 0;
        case Entity_Armor_Kind__Cloth:
            return get_frame_offset__for_cloth_armor(entity);
        case Entity_Armor_Kind__Iron:
            switch (entity->armor_properties.the_kind_of_modification__this_armor_has) {
                default:
                case Entity_Armor_Modification_Kind__None:
                    return get_frame_offset__for_iron_armor(entity);
                case Entity_Armor_Modification_Kind__Diamond:
                    return get_frame_offset__for_iron_diamond_armor(entity);
                case Entity_Armor_Modification_Kind__Amethyst:
                    return get_frame_offset__for_iron_amethyst_armor(entity);
            }
        case Entity_Armor_Kind__Gold:
            switch (entity->armor_properties.the_kind_of_modification__this_armor_has) {
                default:
                case Entity_Armor_Modification_Kind__None:
                    return get_frame_offset__for_gold_armor(entity);
                case Entity_Armor_Modification_Kind__Diamond:
                    return get_frame_offset__for_gold_diamond_armor(entity);
                case Entity_Armor_Modification_Kind__Amethyst:
                    return get_frame_offset__for_gold_amethyst_armor(entity);
            }
            break;
    }
}

uint32_t get_start_frame__of_animation(Entity *entity, 
        enum Sprite_Animation_Kind kind_of_animation) {
    uint32_t frame_offset = 0;
    if (can_entity_kind_have__armor(
                entity->the_kind_of_entity__this_entity_is)) {
        frame_offset = get_frame_offset__from_entity_armor(entity);
    }

    frame_offset += 
        get_frame_offset__for_direction(entity);

    switch (kind_of_animation) {
        default:
            debug_error(
                    "Missing animation implementation for given humanoid kind.");
            return 0;
        case Sprite_Animation_Kind__Idle:
            return frame_offset;
        case Sprite_Animation_Kind__Humanoid__Walk:
            return
                frame_offset
                + SPRITE_FRAME_COL__ENTITY_HUMANOID__WALK
                ;
        case Sprite_Animation_Kind__Humanoid__Use:
            return
                frame_offset
                + SPRITE_FRAME_COL__ENTITY_HUMANOID__USE
                ;
    }
}

void animate_sprite__humanoid(Entity *entity) {
    uint32_t frame_offset = 0;
    if (can_entity_kind_have__armor(
                entity->the_kind_of_entity__this_entity_is)) {
        frame_offset = get_frame_offset__from_entity_armor(entity);
    }

    frame_offset += 
        get_frame_offset__for_direction(entity);
    debug_info("dir: %d", get_frame_offset__for_direction(entity));

    switch (entity->sprite_wrapper.the_kind_of_animation__this_sprite_has) {
        default:
            debug_error("Missing animation implementation for given humanoid kind.");
            break;
        case Sprite_Animation_Kind__Idle:
            entity->sprite_wrapper.frame = frame_offset;
            break;
        case Sprite_Animation_Kind__Humanoid__Walk:
            uint32_t last_frame_of_walk =
                frame_offset
                + SPRITE_FRAME_COL__ENTITY_HUMANOID__USE
                ;
            entity->sprite_wrapper.frame++;
            if (entity->sprite_wrapper.frame >= last_frame_of_walk)
                entity->sprite_wrapper.frame = 
                    frame_offset
                    + SPRITE_FRAME_COL__ENTITY_HUMANOID__WALK
                    ;
            break;
        case Sprite_Animation_Kind__Humanoid__Use:
            uint32_t last_frame_of_use =
                frame_offset 
                + SPRITE_FRAME_COL_GROUP_OFFSET__ENTITY_HUMANOID
                ;
            entity->sprite_wrapper.frame++;
            if (entity->sprite_wrapper.frame >= last_frame_of_use)
                entity->sprite_wrapper.frame =
                    frame_offset
                    + SPRITE_FRAME_COL__ENTITY_HUMANOID__USE
                    ;
            break;
    }
    PLATFORM_update_sprite_gfx__to_current_frame(entity);
}

void set_sprite__animation(Entity *entity, 
        enum Sprite_Animation_Kind kind_of_animation) {
    uint32_t frame =
        get_start_frame__of_animation(
                entity, kind_of_animation);
    entity->sprite_wrapper.frame = frame;
    entity->sprite_wrapper.the_kind_of_animation__this_sprite_has =
        kind_of_animation;
    PLATFORM_update_sprite_gfx__to_current_frame(entity);
}
