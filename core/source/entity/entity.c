#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>
#include <rendering/animate_entity.h>
#include <collisions/hitbox_aabb.h>

#include <debug/debug.h>

bool can_entity_kind_have__armor(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    can_entity_kind_have__armor.");
            return false;
        case Entity_Kind__Zombie:
            return false;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

bool can_entity__move(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    can_entity__move.");
            return false;
        case Entity_Kind__Zombie:
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

bool is_entity__humanoid(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            debug_warning("Unknown entity type in call to\
                    is_entity__humanoid.");
            return false;
        case Entity_Kind__Zombie:
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

void init_entity(Entity *entity, enum Entity_Kind kind_of_entity) {
    entity->the_kind_of_entity__this_entity_is =
        kind_of_entity;

    entity->hitbox.x__chunk =
        entity->hitbox.x = 0;
    entity->hitbox.y__chunk =
        entity->hitbox.y = 0;
    entity->hitbox.z__chunk =
        entity->hitbox.z = 0;

    entity->dispose_handler = 0;
    entity->controller_handler = 0;
    entity->collision_handler = 0;
    entity->tile_collision_handler = 0;

    set_entity__enabled(entity);
    set_entity__is_updating_position(entity);
    set_entity__is_updating_graphics(entity);

    init_sprite_wrapper(
            &entity->sprite_wrapper,
            kind_of_entity);
}

void set_entity__armor(Entity *entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification) {
    entity->armor_properties.the_kind_of_armor__this_armor_is =
        kind_of_armor;
    entity->armor_properties.the_kind_of_modification__this_armor_has =
        kind_of_armor_modification;
}

void set_entity__direction(Entity *entity,
        Direction direction) {
    if (entity->sprite_wrapper.direction == direction)
        return;
    entity->sprite_wrapper.direction = direction;
}

Direction get_entity__direction(Entity *entity) {
    return entity->sprite_wrapper.direction;
}

bool commit_entity_velocity(
        Entity *entity,
        int32_t *old_x__chunk,
        int32_t *old_y__chunk) {
    *old_x__chunk = entity->hitbox.x__chunk;
    *old_y__chunk = entity->hitbox.y__chunk;

    commit_hitbox_velocity(&entity->hitbox);

    if (*old_x__chunk != entity->hitbox.x__chunk 
            || *old_y__chunk != entity->hitbox.y__chunk) {
        return true;
    }
    return false;
}
