#include <entity/entity_manager.h>
#include <rendering/animate_entity.h>
#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>

#include <entity/controllers/controller_player.h>

void init_entity_manager(Entity_Manager *entity_manager) {
    entity_manager->entity_count__quantity_u32 = 0;
    for (uint32_t i=0;i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        set_entity__disabled(&entity_manager->entities[i]);
    }
}

Entity *allocate__entity(Entity_Manager* entity_manager,
        enum Entity_Kind kind_of_entity) {
    // TODO: do better than bellow:
    switch (kind_of_entity) {
        default:
            break;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            if (entity_manager->entity_count__quantity_u32 
                    >= ENTITY_MAXIMUM_QUANTITY_OF__COLLIDABLE) {
                debug_error("Entity limit reached.");
                return 0;
            }
            break;
    }
    uint32_t start = 0;
    if (kind_of_entity == Entity_Kind__Player) {
        start =0;
    } else {
        start = ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS;
    }
    for (uint32_t i = start;
            i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        if (!is_entity__enabled(&entity_manager->entities[i])) {
            init_entity(&entity_manager->entities[i],
                    kind_of_entity);
            entity_manager->entity_count__quantity_u32++;
            return &entity_manager->entities[i];
        }
    }

    debug_error("Failed to allocate new entity.");

    return 0;
}

void release_entity__silently(Entity_Manager* entity_manager, Entity* entity) {
    entity_manager->entity_count__quantity_u32--;
    set_entity__disabled(entity);
    PLATFORM_release_sprite(&entity->sprite_wrapper.sprite);
}
