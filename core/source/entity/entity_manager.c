#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "entity/controllers/collidable_entity_handlers.h"
#include "entity/controllers/humanoid_animation_handler.h"
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

void release_entity_from__entity_manager(Entity_Manager* entity_manager, Entity* entity) {
    entity_manager->entity_count__quantity_u32--;
    set_entity__disabled(entity);
    PLATFORM_release_sprite(&entity->sprite_wrapper.sprite);
}

Entity *get_new__entity(
        Entity_Manager *p_entity_manager,
        enum Entity_Kind kind_of_entity,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    switch (kind_of_entity) {
        default:
            ///
            /// If you're trying to make a player,
            /// call get_new__player instead.
            ///
            debug_error("Failed to get new entity, \
invalid kind_of_entity. get_new__entity(...).");
            break;
        // non-player humanoids:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            return get_new__humanoid(
                    p_entity_manager,
                    kind_of_entity,
                    x__global,
                    y__global,
                    z__global);
    }

    return 0;
}

Entity *get_new__humanoid(
        Entity_Manager *p_entity_manager,
        enum Entity_Kind kind_of_entity,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    Entity *p_entity = allocate__entity(
            p_entity_manager, kind_of_entity);

    if (!p_entity) {
        return 0;
    }

    init_hitbox(
            &p_entity->hitbox, 
            6, 6, 
            x__global, 
            y__global, 
            z__global);

    set_entity__collider(
            p_entity, 
            m_entity_collision_handler);
    set_entity__tile_collider(
            p_entity,
            m_entity_tile_collision_handler);
    set_entity__animator(
            p_entity,
            m_humanoid_animation_handler);

    return p_entity;
}

Entity *get_new__player(
        Entity_Manager *p_entity_manager,
        bool is_local_player,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    Entity *p_player = get_new__humanoid(
            p_entity_manager,
            Entity_Kind__Player,
            x__global,
            y__global,
            z__global);
    if (!p_player) {
        return 0;
    }
    if (is_local_player) {
        p_entity_manager->p_local_player = p_player;
        set_entity__is_not_updating_position(
                p_player);
        set_entity__controller(
                p_player,
                m_controller_for__player);
    }

    return p_player;
}
