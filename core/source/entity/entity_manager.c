#include <entity/entity_manager.h>
#include <rendering/animate_entity.h>
#include <entity/entity.h>
#include <debug/debug.h>

#include <entity/controllers/controller_player.h>

void init_entity_manager(Entity_Manager *entity_manager) {
    entity_manager->entity_count = 0;
    for (uint32_t i=0;i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        set_entity__disabled(&entity_manager->entities[i]);
    }
}

Entity *get_new__player(Entity_Manager* entity_manager,
        bool is_local_player) {
    for (uint32_t i=0;i<ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS;i++) {
        if (!is_entity__enabled(&entity_manager->entities[i])) {
            init_entity(&entity_manager->entities[i],
                    Entity_Kind__Player);
            if (is_local_player) {
                entity_manager->local_player =
                    &entity_manager->entities[i];
                set_entity__is_not_updating_position(
                        entity_manager->local_player);
                set_entity__controller(
                        entity_manager->local_player,
                        m_controller_for__player);
            }
            return &entity_manager->entities[i];
        }
    }

    debug_error("Failed to allocate new entity.");

    return 0;
}

Entity *get_new__entity(Entity_Manager* entity_manager,
        enum Entity_Kind kind_of_entity) {
    for (uint32_t i=
            ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS;
            i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        if (!is_entity__enabled(&entity_manager->entities[i])) {
            init_entity(&entity_manager->entities[i],
                    kind_of_entity);
            return &entity_manager->entities[i];
        }
    }

    debug_error("Failed to allocate new entity.");

    return 0;
}

void release_entity__silently(Entity_Manager* entity_manager, Entity* entity) {
    set_entity__disabled(entity);
}
