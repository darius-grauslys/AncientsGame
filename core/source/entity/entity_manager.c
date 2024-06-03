#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "timer.h"
#include <entity/entity_manager.h>
#include <rendering/animate_entity.h>
#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>

#include <entity/implemented/player/entity__player.h>
#include <entity/implemented/skeleton/entity__skeleton.h>
#include <entity/implemented/zombie/entity__zombie.h>

void initialize_entity_manager(Entity_Manager *entity_manager) {
    entity_manager->entity_count__quantity_u32 = 0;
    for (uint32_t i=0;i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        set_entity__disabled(&entity_manager->entities[i]);
    }
}

Entity *allocate__entity(Entity_Manager* entity_manager,
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4) {
    // TODO: do better than bellow:
    switch (kind_of_entity) {
        default:
            debug_abort("allocate__entity, unhandled entity_kind %d.",
                    kind_of_entity);
            debug_warning("Did you forget to include your new entity kind within entity_manager.c, allocate__entity?");
            return 0;
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
        start = 0;
    } else {
        start = ENTITY_MAXIMUM_QUANTITY_OF__PLAYERS;
    }

    Entity *p_entity = 0;
    for (uint32_t i = start;
            i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        if (is_entity__enabled(&entity_manager->entities[i])) {
            continue;
        }

        entity_manager->entity_count__quantity_u32++;
        p_entity = &entity_manager->entities[i];
        break;
    }
    
    if (!p_entity) {
        debug_error("allocate__entity, failed to allocate new entity.");
        debug_warning("Is the entity limit reached?");
        return 0;
    }
    
    switch (kind_of_entity) {
        case Entity_Kind__Player:
            initialize_entity_as__player(
                    p_entity,
                    position__3i32F4);
            break;
        case Entity_Kind__Skeleton:
            initialize_entity_as__skeleton(
                    p_entity,
                    position__3i32F4);
            break;
        case Entity_Kind__Zombie:
            initialize_entity_as__zombie(
                    p_entity,
                    position__3i32F4);
            break;
    }

    return p_entity;
}

void release_entity_from__entity_manager(Entity_Manager* entity_manager, Entity* entity) {
    entity_manager->entity_count__quantity_u32--;
    set_entity__disabled(entity);
    PLATFORM_release_sprite(&entity->sprite_wrapper.sprite);
}
