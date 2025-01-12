#include "defines.h"
#include "defines_weak.h"
#include "entity/handlers/ai/ai_handler__debug.h"
#include "entity/humanoid.h"
#include "game.h"
#include "platform.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/gfx_context.h"
#include "rendering/sprite.h"
#include "rendering/sprite_gfx_allocator_manager.h"
#include "rendering/texture_strings.h"
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
            p_PLATFORM_graphics_window,
            p_entity,
            Entity_Kind__Player,
            position__3i32F4,
            7, 7);
    set_entity__disposer(
            p_entity,
            m_entity_dispose_handler__default);
    set_entity__body_handler(
			p_entity, 
            m_entity_body_handler__living);
    set_entity__ai_handler(
			p_entity,
            m_entity_ai_handler__player);
    set_entity__ai_handler(
			p_entity,
            m_entity_ai_handler__player);
            //m_entity_ai_handler__debug);
    set_entity__collider(
			p_entity,
            m_entity_collision_handler__default);
    set_entity__tile_collider(
			p_entity,
            m_entity_tile_collision_handler__default);
    set_entity__animator(
			p_entity,
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

bool f_sprite_gfx_allocator__player(
        Gfx_Context *p_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Wrapper *p_sprite_wrapper,
        u32 enum_value) {
    // assume enum value is player.

    Aliased_Texture_Manager *p_aliased_texture_manager =
        get_p_aliased_texture_manager_from__gfx_context(p_gfx_context);
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__gfx_context(p_gfx_context);

    PLATFORM_Texture *p_PLATFORM_texture_for__player =
        get_p_PLATFORM_texture_by__alias(
                p_aliased_texture_manager, 
                name_of__texture__player__c_str);

    if (!p_PLATFORM_texture_for__player)
        return 0;
    
    p_sprite_wrapper->p_sprite =
        PLATFORM_allocate_sprite(
                p_PLATFORM_gfx_context, 
                p_PLATFORM_gfx_window,
                p_PLATFORM_texture_for__player, 
                TEXTURE_FLAG__SIZE_16x16);
    return p_sprite_wrapper->p_sprite;
}
