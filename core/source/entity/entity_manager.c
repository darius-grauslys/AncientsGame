#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/controllers/body/collidable_entity_handlers.h"
#include "entity/controllers/animation/humanoid_animation_handler.h"
#include "entity/controllers/body/humanoid_body_handler.h"
#include "entity/controllers/body/undead_body_handler.h"
#include "timer.h"
#include <entity/entity_manager.h>
#include <rendering/animate_entity.h>
#include <entity/entity.h>
#include <debug/debug.h>
#include <rendering/sprite.h>

#include <entity/controllers/ai/controller_player.h>

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
        start = 0;
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

void init_entity_as__humanoid(
        Entity *p_entity,
        Quantity__u8 width,
        Quantity__u8 height,
        Quantity__u8 max_quantity_of__hearts,
        Quantity__u8 max_quantity_of__energy_orbs,
        Vector__3i32F4 position__3i32F4) {

    set_entity__collider(
            p_entity, 
            m_entity_collision_handler);
    set_entity__tile_collider(
            p_entity,
            m_entity_tile_collision_handler);
    set_entity__animator(
            p_entity,
            m_humanoid_animation_handler);

    init_hitbox(
            &p_entity->hitbox, 
            width, height,
            position__3i32F4);

    p_entity->hearts.max_quantity_of__resource_symbols =
        max_quantity_of__hearts;
    p_entity->energy_orbs.max_quantity_of__resource_symbols =
        max_quantity_of__energy_orbs;

    p_entity->humanoid__primary_sustenance__u8 = 128;
    p_entity->humanoid__secondary_sustenance__u8 = 128;
    init_timer_u16(
            &p_entity->humanoid__homeostasis__timer_u16, 
            MASK(16));

    for (Index__u8 heart_index=0;
            heart_index
                < p_entity->hearts.max_quantity_of__resource_symbols;
            heart_index++) {
        p_entity->hearts.resource_symbols[heart_index] =
            Heart_Kind__Full_Normal;
    }
    for (Index__u8 energy_orb_index=0;
            energy_orb_index
                < p_entity->energy_orbs.max_quantity_of__resource_symbols;
            energy_orb_index++) {
        p_entity->energy_orbs.resource_symbols[energy_orb_index] =
            Heart_Kind__Full_Normal;
    }
}

void init_entity_as__player(
        Entity *p_player,
        Vector__3i32F4 position__3i32F4) {

    init_entity_as__humanoid(
            p_player, 
            6, 6, 
            10, 10,
            position__3i32F4);

    set_entity__is_not_updating_position(
            p_player);
    set_entity__body_handler(
            p_player, 
            m_handler_for__body_living);
    set_entity__ai_handler(
            p_player,
            m_handler_for__ai_player);
}

void init_entity_as__zombie(
        Entity *p_zombie,
        Vector__3i32F4 position__3i32F4) {

    init_entity_as__humanoid(
            p_zombie, 
            6, 6, 
            8, 8,
            position__3i32F4);

    set_entity__body_handler(
            p_zombie, 
            m_handler_for__body_undead);
}

void init_entity_as__skeleton(
        Entity *p_skeleton,
        Vector__3i32F4 position__3i32F4) {

    init_entity_as__humanoid(
            p_skeleton, 
            6, 6, 
            15, 15,
            position__3i32F4);
    set_entity__body_handler(
            p_skeleton, 
            m_handler_for__body_undead);
}

Entity *get_new__entity(
        Entity_Manager *p_entity_manager,
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4) {
    Entity *p_entity = allocate__entity(
            p_entity_manager, 
            kind_of_entity);
    switch (kind_of_entity) {
        default:
            debug_error("Failed to get new entity, \
invalid kind_of_entity %d get_new__entity(...).", kind_of_entity);
            break;
        // non-player humanoids:
        case Entity_Kind__Zombie:
            init_entity_as__zombie(
                    p_entity,
                    position__3i32F4);
            break;
        case Entity_Kind__Skeleton:
            init_entity_as__skeleton(
                    p_entity,
                    position__3i32F4);
            break;
        case Entity_Kind__Player:
            init_entity_as__player(
                    p_entity,
                    position__3i32F4);
            // TODO: don't assign local player here!
            if (!p_entity_manager->p_local_player) {
                p_entity_manager->p_local_player =
                    p_entity;
            }
            break;
    }

    return p_entity;
}
