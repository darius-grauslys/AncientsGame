#include "defines_weak.h"
#include <entity/humanoid.h>
#include <entity/entity.h>
#include <inventory/inventory.h>

void initialize_entity_as__humanoid(
        Entity *p_entity, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4,
        Quantity__u32 width,
        Quantity__u32 height,
        m_Entity_Dispose_Handler m_entity_dispose_handler,
        m_Entity_Body_Handler m_entity_body_handler,
        m_Entity_AI_Handler m_entity_ai_handler,
        m_Entity_Collision_Handler m_entity_collision_handler,
        m_Entity_Tile_Collision_Handler m_entity_tile_collision_handler,
        m_Entity_Animation_Handler m_entity_animation_handler) {
    initialize_entity(
            p_entity, 
            kind_of_entity, 
            position__3i32F4, 
            width, 
            height, 
            m_entity_dispose_handler, 
            m_entity_body_handler, 
            m_entity_ai_handler, 
            m_entity_collision_handler, 
            m_entity_tile_collision_handler, 
            m_entity_animation_handler);
    initialize_inventory(
            get_p_inventory_from__humanoid(p_entity));
#warning TODO: impl armor init and homeo
}

bool is_entity_a__humanoid(Entity *entity) {
    switch (entity->the_kind_of_entity__this_entity_is) {
        default:
            return false;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            return true;
    }
}
