#include "defines.h"
#include "defines_weak.h"
#include <rendering/animate_humanoid.h>
#include <entity/entity.h>

uint32_t get_animation_frame_offset_for__armor(Entity *entity) {
    switch (entity->humanoid__armor_properties.the_kind_of_armor__this_armor_is) {
        default:
        case Entity_Armor_Kind__None:
            return 0;
        case Entity_Armor_Kind__Cloth:
            return get_animation_frame_offset_for__group(
                    SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_CLOTH);
        case Entity_Armor_Kind__Iron:
            switch (entity->humanoid__armor_properties.the_kind_of_modification__this_armor_has) {
                default:
                case Entity_Armor_Modification_Kind__None:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON);
                case Entity_Armor_Modification_Kind__Rusted:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_IRON__RUSTED);
            }
        case Entity_Armor_Kind__Steel:
            switch (entity->humanoid__armor_properties.the_kind_of_modification__this_armor_has) {
                default:
                case Entity_Armor_Modification_Kind__None:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_STEEL);
                case Entity_Armor_Modification_Kind__Diamond:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_STEEL__DIAMOND);
                case Entity_Armor_Modification_Kind__Amethyst:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_STEEL__AMETHYST);
            }
        case Entity_Armor_Kind__Gold:
            switch (entity->humanoid__armor_properties.the_kind_of_modification__this_armor_has) {
                default:
                case Entity_Armor_Modification_Kind__None:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD);
                case Entity_Armor_Modification_Kind__Diamond:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD__DIAMOND);
                case Entity_Armor_Modification_Kind__Amethyst:
                    return get_animation_frame_offset_for__group(
                            SPRITE_FRAME_GROUP_INDEX__ENTITY_HUMANOID__ARMOR_GOLD__AMETHYST);
            }
            break;
    }
}

Sprite_Frame_Index__u8 f_get_inital_sprite_frame_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind) {

    uint32_t frame_offset = 0;
    uint32_t frame_offset__without_direction = 0;
    if (can_entity_kind_have__armor(
                humanoid->the_kind_of_entity__this_entity_is)) {
        frame_offset = 
            get_animation_frame_offset_for__armor(humanoid)
            + get_animation_frame_offset_for__direction__of_humanoid_armored(
                    humanoid->sprite_wrapper.direction);
        frame_offset__without_direction =
            get_animation_frame_offset_for__armor(humanoid)
            + get_animation_frame_offset_for__direction__of_humanoid_armored(
                    DIRECTION__NONE);
    } else {
        frame_offset = 
            get_animation_frame_offset_for__direction__of_humanoid_unarmored(
                    humanoid->sprite_wrapper.direction);
        frame_offset__without_direction = 
            get_animation_frame_offset_for__direction__of_humanoid_unarmored(
                    DIRECTION__NONE);
    }

    switch (animation_kind) {
        default:
        case Sprite_Animation_Kind__Idle:
            return frame_offset;
        case Sprite_Animation_Kind__Humanoid__Walk:
            return frame_offset
                + SPRITE_FRAME_COL__ENTITY_HUMANOID__WALK;
        case Sprite_Animation_Kind__Humanoid__Use:
            return frame_offset
                + SPRITE_FRAME_COL__ENTITY_HUMANOID__USE;
        case Sprite_Animation_Kind__Humanoid__Hurt:
            return frame_offset__without_direction
                + SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                + SPRITE_FRAME_COL__ENTITY_HUMANOID__HURT;
        case Sprite_Animation_Kind__Humanoid__Die:
            return frame_offset__without_direction
                + SPRITE_FRAME_ROW_GROUP_OFFSET__ENTITY_HUMANOID
                + SPRITE_FRAME_COL__ENTITY_HUMANOID__DIE;
    }
}

Sprite_Frame_Index__u8 f_get_final_sprite_frame_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind) {
    Sprite_Frame_Index__u8 offset =
        f_get_inital_sprite_frame_for__humanoid_animation(
                humanoid, animation_kind);

    switch (animation_kind) {
        default:
        case Sprite_Animation_Kind__Idle:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__IDLE;
        case Sprite_Animation_Kind__Humanoid__Walk:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__WALK;
        case Sprite_Animation_Kind__Humanoid__Use:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__USE;
        case Sprite_Animation_Kind__Humanoid__Hurt:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__HURT;
        case Sprite_Animation_Kind__Humanoid__Die:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__DIE;
    }
}

Quantity__u32 f_get_animation_speed_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind) {
    //TODO: magic number timers
    switch (animation_kind) {
        default:
        case Sprite_Animation_Kind__Idle:
            return 1;
        case Sprite_Animation_Kind__Humanoid__Walk:
        case Sprite_Animation_Kind__Humanoid__Use:
        case Sprite_Animation_Kind__Humanoid__Hurt:
        case Sprite_Animation_Kind__Humanoid__Die:
            return 8;
    }
}

Quantity__u32 f_get_animation_duration_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind) {
    //TODO: magic number timers
    switch (animation_kind) {
        default:
        case Sprite_Animation_Kind__Idle:
            return 1;
        case Sprite_Animation_Kind__Humanoid__Walk:
            return 16;
        case Sprite_Animation_Kind__Humanoid__Use:
            return 24;
        case Sprite_Animation_Kind__Humanoid__Hurt:
            return 8;
        case Sprite_Animation_Kind__Humanoid__Die:
            return 64;
    }
}

void poll_humanoid_animation__transition(
        Entity *humanoid) {
    bool force = 
        humanoid->direction
        != humanoid->sprite_wrapper.direction;
    if (force) {
        humanoid->sprite_wrapper.direction =
            humanoid->direction;
        goto poll;
    }
    if (is_animation__not_running(humanoid->sprite_wrapper)) {
        animate_humanoid__idle(humanoid);
    }
poll:
    poll_entity_animation__transition(
            humanoid, 
            f_get_inital_sprite_frame_for__humanoid_animation, 
            f_get_final_sprite_frame_for__humanoid_animation,
            force);
}
