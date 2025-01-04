#include "defines_weak.h"
#include "entity/handlers/ai/ai_handler__chase_melee.h"
#include "entity/humanoid.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/sprite.h"
#include "rendering/texture_strings.h"
#include "world/tile_vectors.h"
#include <entity/implemented/skeleton/entity__skeleton.h>
#include <entity/entity.h>

#include <entity/handlers/entity_handlers.h>
#include <entity/handlers/ai/ai_handler__dummy.h>
#include <entity/handlers/body/body_handler__living.h>
#include <entity/handlers/animation/animation_handler__humanoid.h>
#include <entity/handlers/collision/collision_handler__default.h>

void initialize_entity_as__skeleton(
        Game *p_game,
        PLATFORM_Graphics_Window 
            *p_PLATFORM_graphics_window,
        Entity *p_entity, 
        Vector__3i32F4 position__3i32F4) {
    initialize_entity_as__humanoid(
            p_game,
            p_PLATFORM_graphics_window,
            p_entity,
            Entity_Kind__Skeleton,
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
            m_entity_ai_handler__chase_melee);
    set_entity__collider(
			p_entity,
            m_entity_collision_handler__default);
    set_entity__tile_collider(
			p_entity,
            m_entity_tile_collision_handler__default);
    set_entity__animator(
			p_entity,
            m_entity_animation_handler__humanoid);

    p_entity->the_kind_of__audio_effect_for__alert =
        Audio_Effect_Kind__Monster__Skeleton__Alert;
    p_entity->the_kind_of__audio_effect_for__die =
        Audio_Effect_Kind__Monster__Skeleton__Die;

    p_entity->goal__position__3i32F4 =
        position__3i32F4;

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
}

bool f_sprite_gfx_allocator__skeleton(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Wrapper *p_sprite_wrapper,
        u32 enum_value) {
    // assume enum value is skeleton.

    Aliased_Texture_Manager *p_aliased_texture_manager =
        get_p_aliased_texture_manager_from__game(p_game);
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    PLATFORM_Texture *p_PLATFORM_texture_for__skeleton =
        get_p_PLATFORM_texture_by__alias(
                p_aliased_texture_manager, 
                name_of__texture__skeleton__c_str);

    if (!p_PLATFORM_texture_for__skeleton)
        return 0;
    
    p_sprite_wrapper->p_sprite = 
        PLATFORM_allocate_sprite(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_gfx_window,
            p_PLATFORM_texture_for__skeleton, 
            TEXTURE_FLAG__SIZE_16x16);
    return p_sprite_wrapper->p_sprite;
}
