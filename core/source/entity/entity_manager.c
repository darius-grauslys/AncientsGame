#include <entity/entity_manager.h>
#include <rendering/animate_entity.h>
#include <entity/entity.h>
#include <debug/debug.h>

void init_entity_manager(Entity_Manager *entity_manager) {
    entity_manager->entity_count = 0;
    for (uint32_t i=0;i<ENTITY_MAXIMUM__QUANTITY_OF;i++) {
        set_entity__disabled(&entity_manager->entities[i]);
    }
}

Entity *get_new__player(Entity_Manager* manager) {
    for (uint32_t i=0;i<ENTITY_PLAYER_MAXIMUM__QUANTITY_OF;i++) {
        if (!is_entity__enabled(&manager->entities[i])) {
            init_entity(&manager->entities[i],
                    Entity_Kind__Player);
            return &manager->entities[i];
        }
    }

    debug_error("Failed to allocate new entity.");

    return 0;
}

Entity *get_new__entity(Entity_Manager* manager,
        enum Entity_Kind kind_of_entity) {
    for (uint32_t i=
            ENTITY_PLAYER_MAXIMUM__QUANTITY_OF;
            i<ENTITY_MAXIMUM__QUANTITY_OF;i++) {
        if (!is_entity__enabled(&manager->entities[i])) {
            init_entity(&manager->entities[i],
                    kind_of_entity);
            return &manager->entities[i];
        }
    }

    debug_error("Failed to allocate new entity.");

    return 0;
}

void release_entity__silently(Entity_Manager* manager, Entity* entity) {
    set_entity__disabled(entity);
}
