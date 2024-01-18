#include <entity/entity.h>
#include <rendering/animate_entity.h>
#include <rendering/animate_sprite.h>
#include <debug/debug.h>

uint32_t get_animation_frame_offset_for__direction(
        Direction direction,
        uint32_t cols_per_row) {
    switch (direction) {
        default:
        case DIRECTION__EAST:
        case DIRECTION__WEST:
            return get_animation_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__SIDE_FACING,
                    cols_per_row);
        case DIRECTION__SOUTH:
            return get_animation_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__FORWARD_FACING,
                    cols_per_row);
        case DIRECTION__NORTH:
            return get_animation_frame(0,
                    SPRITE_FRAME_ROW__ENTITY_HUMANOID__BACK_FACING,
                    cols_per_row);
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

uint32_t get_animation_starting_frame_for__humanoid_entity(Entity *entity, 
        enum Sprite_Animation_Kind kind_of_animation) {
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

uint32_t get_animation_starting_frame_for__entity(Entity *entity, 
        enum Sprite_Animation_Kind kind_of_animation) {
    // TODO: this debug_warning is true, but annoying atm.
    // debug_warning("get_animation_starting_frame_for__entity not finished.");
    return get_animation_starting_frame_for__humanoid_entity(entity, 
            kind_of_animation);
}

void set_entity_animation(Entity *entity,
        enum Sprite_Animation_Kind kind_of_animation) {
    entity->sprite_wrapper.the_kind_of_animation__this_sprite_has =
        kind_of_animation;
    entity->sprite_wrapper.frame =
        get_animation_starting_frame_for__entity(entity,
                kind_of_animation);
    PLATFORM_update_sprite_gfx__to_current_frame(&entity->sprite_wrapper);
}

void animate_entity__as_humanoid(Entity *entity) {
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
    PLATFORM_update_sprite_gfx__to_current_frame(
            &entity->sprite_wrapper);
}

void animate_entity(Entity *entity) {
    if (is_entity_not__updating_graphics(entity))
        return;
    switch (entity->the_kind_of_entity__this_entity_is) {
        default:
            debug_error("Missing animation implementation for given entity kind.");
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            uint32_t frame = entity->sprite_wrapper.frame;
            animate_entity__as_humanoid(entity);
            break;
    }
    PLATFORM_update_sprite_gfx__to_current_frame(
            &entity->sprite_wrapper);
}
