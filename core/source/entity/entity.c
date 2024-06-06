#include "defines.h"
#include <entity/entity.h>
#include <entity/handlers/entity_handlers.h>
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

void initialize_entity(
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        m_Entity_Dispose_Handler m_entity_dispose_handler,
        m_Entity_Body_Handler m_entity_body_handler,
        m_Entity_AI_Handler m_entity_ai_handler,
        m_Entity_Collision_Handler m_entity_collision_handler,
        m_Entity_Tile_Collision_Handler m_entity_tile_collision_handler,
        m_Entity_Animation_Handler m_entity_animation_handler) {
    p_entity->the_kind_of_entity__this_entity_is =
        kind_of_entity;

    set_hitbox__position_with__3i32F4(
            &p_entity->hitbox, 
            position__3i32F4);

    p_entity->m_entity_dispose_handler = 
        (m_entity_dispose_handler)
        ? m_entity_dispose_handler
        : m_entity_dispose_handler__default
        ;
    p_entity->m_entity_body_handler = 
        m_entity_body_handler;
    p_entity->m_entity_ai_handler = 
        m_entity_ai_handler;
    p_entity->m_entity_collision_handler = 
        m_entity_collision_handler;
    p_entity->m_entity_tile_collision_handler =
        m_entity_tile_collision_handler;
    p_entity->m_entity_animation_handler =
        m_entity_animation_handler;

    p_entity->entity_flags = ENTITY_FLAG__NONE;

    set_entity__enabled(p_entity);
    set_entity__is_updating_position(p_entity);
    set_entity__is_updating_graphics(p_entity);

    initialize_sprite_wrapper_for__entity(
            p_entity);
}

void set_entity__armor(Entity *p_entity,
        enum Entity_Armor_Kind kind_of_armor,
        enum Entity_Armor_Modification_Kind kind_of_armor_modification) {
    p_entity->humanoid__armor_properties.the_kind_of_armor__this_armor_is =
        kind_of_armor;
    p_entity->humanoid__armor_properties.the_kind_of_modification__this_armor_has =
        kind_of_armor_modification;
}
