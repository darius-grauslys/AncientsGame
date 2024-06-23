#ifndef HUMANOID_H
#define HUMANOID_H

#include <defines.h>

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
        m_Entity_Animation_Handler m_entity_animation_handler);

static inline
Inventory *get_p_inventory_from__humanoid(
        Entity *p_entity) {
    return &p_entity->humanoid__inventory;
}

bool is_entity_a__humanoid(Entity *entity);
    
//TODO: this should be an entity thing
//      not a humanoid thing.
static void inline set_humanoid__direction(
        Entity *humanoid,
        Direction__u8 direction) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                humanoid);
        return;
    }
#endif
    humanoid->direction = direction;
}

static Direction__u8 inline get_humanoid__direction(
        Entity *humanoid) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                humanoid);
        return DIRECTION__NONE;
    }
#endif
    return humanoid->direction;
}

static bool inline is_humanoid__undead(
        Entity *humanoid) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                humanoid);
        return false;
    }
#endif
    return (bool)(humanoid->humanoid_flags 
            & HUMANOID_FLAG__IS_UNDEAD);
}

static bool inline does_humanoid_have__divine_providence(
        Entity *p_humanoid) {
#ifndef NDEBUG
    if (!is_entity_a__humanoid(p_humanoid)) {
        debug_error("Treated non-humanoid %p as humanoid!",
                p_humanoid);
        return false;
    }
#endif
    return (bool)(p_humanoid->humanoid_flags 
            & HUMANOID_FLAG__HAS_DIVINE_PROVIDENCE);
}

#endif
