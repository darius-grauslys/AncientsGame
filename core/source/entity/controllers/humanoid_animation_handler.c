#include <entity/controllers/humanoid_animation_handler.h>

uint32_t get_animation_starting_frame_for__humanoid_entity(Entity *entity) {
    uint32_t frame_offset = 0;
    if (can_entity_kind_have__armor(
                entity->the_kind_of_entity__this_entity_is)) {
        frame_offset = 
            get_animation_frame_offset_for__armor(entity)
            + get_animation_frame_offset_for__direction__of_humanoid_armored(
                    entity->sprite_wrapper.direction);
    } else {
        frame_offset = 
            get_animation_frame_offset_for__direction__of_humanoid_unarmored(
                    entity->sprite_wrapper.direction);
    }

    switch (entity->sprite_wrapper.the_kind_of_animation__this_sprite_has) {
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

uint32_t get_animation_frame_offset_for__armor(Entity *entity) {
    switch (entity->armor_properties.the_kind_of_armor__this_armor_is) {
        default:
        case Entity_Armor_Kind__None:
            return 0;
        case Entity_Armor_Kind__Cloth:
            return get_animation_frame_offset_for__cloth_armor(entity);
        case Entity_Armor_Kind__Iron:
            switch (entity->armor_properties.the_kind_of_modification__this_armor_has) {
                default:
                case Entity_Armor_Modification_Kind__None:
                    return get_animation_frame_offset_for__iron_armor(entity);
                case Entity_Armor_Modification_Kind__Diamond:
                    return get_animation_frame_offset_for__iron_diamond_armor(entity);
                case Entity_Armor_Modification_Kind__Amethyst:
                    return get_animation_frame_offset_for__iron_amethyst_armor(entity);
            }
        case Entity_Armor_Kind__Gold:
            switch (entity->armor_properties.the_kind_of_modification__this_armor_has) {
                default:
                case Entity_Armor_Modification_Kind__None:
                    return get_animation_frame_offset_for__gold_armor(entity);
                case Entity_Armor_Modification_Kind__Diamond:
                    return get_animation_frame_offset_for__gold_diamond_armor(entity);
                case Entity_Armor_Modification_Kind__Amethyst:
                    return get_animation_frame_offset_for__gold_amethyst_armor(entity);
            }
            break;
    }
}

void m_humanoid_animation_handler(Entity *entity, Timer timer) {
    uint32_t animation_frame_length = 0;
    //TODO: profile the performace of this invocation:
    uint32_t frame__initial =
        get_animation_starting_frame_for__humanoid_entity(
                entity);

    switch (entity->sprite_wrapper
            .the_kind_of_animation__this_sprite_has) {
        default:
            debug_error("Missing animation implementation \
for given humanoid kind.");
            break;
        case Sprite_Animation_Kind__Idle:
            entity->sprite_wrapper.frame= 
                entity->sprite_wrapper.frame;
            break;
        case Sprite_Animation_Kind__Humanoid__Walk:
            //TODO: magic number on timer
            if (timer % 32)
                return;
            animation_frame_length = 
                SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__WALK;
            break;
        case Sprite_Animation_Kind__Humanoid__Use:
            if (timer % 32)
                return;
            animation_frame_length = 
                SPRITE_ANIMATION_FRAME_COUNT__ENTITY_HUMANOID__USE;
            break;
    }
    entity->sprite_wrapper.frame++;

    if (entity->sprite_wrapper.frame
            - frame__initial
            > animation_frame_length) {
        entity->sprite_wrapper.frame =
            frame__initial;
    }

    PLATFORM_update_sprite_gfx__to_current_frame(
            &entity->sprite_wrapper);
}
