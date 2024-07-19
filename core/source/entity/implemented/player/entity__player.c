#include "defines.h"
#include "defines_weak.h"
#include "entity/humanoid.h"
#include "platform.h"
#include "rendering/sprite.h"
#include <entity/implemented/player/entity__player.h>
#include <entity/implemented/player/ai/ai_handler__player.h>
#include <entity/entity.h>

#include <entity/handlers/entity_handlers.h>
#include <entity/handlers/body/body_handler__living.h>
#include <entity/handlers/animation/animation_handler__humanoid.h>
#include <entity/handlers/collision/collision_handler__default.h>

void initialize_entity_as__player(
        Game *p_game,
        PLATFORM_Graphics_Window 
            *p_PLATFORM_graphics_window,
        Entity *p_entity, 
        Vector__3i32F4 position__3i32F4) {
    initialize_entity_as__humanoid(
            p_game,
            p_entity,
            Entity_Kind__Player,
            position__3i32F4,
            8, 8);
    set_entity__disposer(
            p_entity,
            m_entity_dispose_handler__default);
    set_entity__body_handler(
			p_entity, 
            m_entity_body_handler__living);
    set_entity__ai_handler(
			p_entity,
            m_entity_ai_handler__player);
    set_entity__collider(
			p_entity,
            m_entity_collision_handler__default);
    set_entity__tile_collider(
			p_entity,
            m_entity_tile_collision_handler__default);
    set_entity__animator(
			p_entity,
            m_entity_animation_handler__humanoid);

    initialize_sprite_wrapper_for__entity_with__sprite_allocation(
            p_PLATFORM_graphics_window,
            p_entity);

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
