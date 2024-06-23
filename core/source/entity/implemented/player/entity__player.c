#include "defines.h"
#include "entity/humanoid.h"
#include <entity/implemented/player/entity__player.h>
#include <entity/implemented/player/ai/ai_handler__player.h>
#include <entity/entity.h>

#include <entity/handlers/entity_handlers.h>
#include <entity/handlers/body/body_handler__living.h>
#include <entity/handlers/animation/animation_handler__humanoid.h>
#include <entity/handlers/collision/collision_handler__default.h>

void initialize_entity_as__player(
        Entity *p_entity, 
        Vector__3i32F4 position__3i32F4) {
    initialize_entity_as__humanoid(
            p_entity,
            Entity_Kind__Player,
            position__3i32F4,
            8, 8,
            m_entity_dispose_handler__default,
            m_entity_body_handler__living,
            m_entity_ai_handler__player,
            m_entity_collision_handler__default,
            m_entity_tile_collision_handler__default,
            m_entity_animation_handler__humanoid);

    p_entity->hearts.resource_symbols[0] = Heart_Kind__Full_Normal;

    p_entity->hearts.max_quantity_of__resource_overflow = 0;
    p_entity->hearts.max_quantity_of__resource_symbols = 10;
    p_entity
        ->energy_orbs.max_quantity_of__resource_overflow = 0;
    p_entity
        ->energy_orbs.max_quantity_of__resource_symbols = 10;

    p_entity->humanoid__primary_sustenance__u8 = 128;
    p_entity->humanoid__secondary_sustenance__u8 = 128;

    p_entity->humanoid__homeostasis__i8 = 0;

    // set_entity__is_not_updating_position(p_entity);
}
