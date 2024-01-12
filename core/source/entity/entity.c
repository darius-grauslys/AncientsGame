#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>
#include <rendering/animate_entity.h>

bool can_entity_kind_have__armor(enum Entity_Kind kind_of_entity) {
    switch (kind_of_entity) {
        default:
            return false;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
            return true;
    }
}

void init_entity(Entity *entity, enum Entity_Kind kind_of_entity) {
    entity->the_kind_of_entity__this_entity_is =
        kind_of_entity;

    debug_warning("init_entity is not complete.");

    init_sprite_wrapper(
            &entity->sprite_wrapper,
            entity);
}

void set_entity__armor(Entity *entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification) {
    entity->armor_properties.the_kind_of_armor__this_armor_is =
        kind_of_armor;
    entity->armor_properties.the_kind_of_modification__this_armor_has =
        kind_of_armor_modification;
    set_animation__of_entity(entity,
            entity->sprite_wrapper.the_kind_of_animation__this_sprite_has);
}
