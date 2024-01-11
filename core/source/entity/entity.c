#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>

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
