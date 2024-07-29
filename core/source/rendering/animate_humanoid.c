#include "defines.h"
#include "defines_weak.h"
#include "numerics.h"
#include "rendering/animate_sprite.h"
#include "timer.h"
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

Sprite_Frame_Index__u8 get_inital_sprite_frame_for__humanoid_animation(
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

Sprite_Frame_Index__u8 get_final_sprite_frame_for__humanoid_animation(
        Entity *humanoid,
        enum Sprite_Animation_Kind animation_kind) {
    Sprite_Frame_Index__u8 offset =
        get_inital_sprite_frame_for__humanoid_animation(
                humanoid, animation_kind);

    switch (animation_kind) {
        default:
        case Sprite_Animation_Kind__Idle:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__IDLE - 1;
        case Sprite_Animation_Kind__Humanoid__Walk:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__WALK - 1;
        case Sprite_Animation_Kind__Humanoid__Use:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__USE - 1;
        case Sprite_Animation_Kind__Humanoid__Hurt:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__HURT - 1;
        case Sprite_Animation_Kind__Humanoid__Die:
            return offset
                + SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__DIE - 1;
    }
}

void set_animation_for__humanoid_with__timer_modification(
        Entity *p_humanoid,
        enum Sprite_Animation_Kind the_kind_of__animation,
        bool is_keeping__timer) {
    Sprite_Wrapper *p_sprite_wrapper = 
        get_p_sprite_wrapper_from__entity(
                p_humanoid);
    if (is_animation_playing__this_kind_of__animation(
                p_sprite_wrapper, 
                Sprite_Animation_Kind__Humanoid__Die)) {
        return;
    }
    p_sprite_wrapper->the_kind_of_animation__this_sprite_has =
        the_kind_of__animation;
    switch (the_kind_of__animation) {
        default:
            p_sprite_wrapper->animation_timer__u32
                .start__u32 = 0;
            break;
        case Sprite_Animation_Kind__Humanoid__Hurt:
            p_sprite_wrapper->animation_timer__u32
                .start__u32 = 
                (ANIMATION_BIT_MASK__TICK_RATE+1)
                * SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__HURT
                ;
            break;
        case Sprite_Animation_Kind__Humanoid__Use:
            p_sprite_wrapper->animation_timer__u32
                .start__u32 = 
                (ANIMATION_BIT_MASK__TICK_RATE+1)
                * SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__USE
                ;
            break;
        case Sprite_Animation_Kind__Humanoid__Walk:
            p_sprite_wrapper->animation_timer__u32
                .start__u32 = 
                (ANIMATION_BIT_MASK__TICK_RATE+1)
                * SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__WALK
                ;
            break;
        case Sprite_Animation_Kind__Humanoid__Die:
            p_sprite_wrapper->animation_timer__u32
                .start__u32 = 
                (ANIMATION_BIT_MASK__TICK_RATE+1)
                * 16
                ;
            break;
    }
    if (!is_keeping__timer) {
        reset_timer_u32(&p_sprite_wrapper->animation_timer__u32);
    }
    Index__u8 frame__initial =
        get_inital_sprite_frame_for__humanoid_animation(
                p_humanoid, 
                the_kind_of__animation);
    Index__u8 frame__final =
        get_final_sprite_frame_for__humanoid_animation(
                p_humanoid, 
                the_kind_of__animation);
    Index__u8 frame__current =
        (is_keeping__timer)
        ? add_u8__clamped(
                frame__initial, 
                get_time_elapsed_from__timer_u32(
                    &p_sprite_wrapper->animation_timer__u32)
                / (ANIMATION_BIT_MASK__TICK_RATE+1), 
                frame__final)
        : frame__initial
        ;
    set_animation_and__timer(
            p_sprite_wrapper, 
            the_kind_of__animation, 
            frame__initial, 
            frame__current, 
            frame__final,
            p_sprite_wrapper->animation_timer__u32);
    PLATFORM_update_sprite_gfx__to_current_frame(
            get_p_sprite_wrapper_from__entity(p_humanoid));
}

