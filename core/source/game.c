#include "defines_weak.h"
#include "platform.h"
#include "scene/scene_manager.h"
#include <game.h>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <debug/debug.h>
#include <input/input.h>
#include <world/chunk_manager.h>
#include <rendering/gfx_context.h>
#include <rendering/animate_entity.h>
#include <rendering/render_entity.h>
#include <world/world.h>
#include <timer.h>

#include <entity/handlers/collision/collision_handler__default.h>
#include <entity/handlers/entity_handlers.h>
#include <entity/handlers/ai/ai_handler__dummy.h>
#include <entity/handlers/animation/animation_handler__humanoid.h>

#include <entity/implemented/player/ai/ai_handler__player.h>

#include <collisions/hitbox_aabb.h>
#include <collisions/collision_manager.h>

#include <world/chunk.h>
#include <world/tile.h>

#include <ui/ui_manager.h>

void initialize_game(
        Game *p_game,
        m_Game_Action_Handler m_game_action_handler) {
    PLATFORM_initialize_gfx_context(&p_game->gfx_context);
    initialize_ui_manager(&p_game->ui_manager);
    initialize_scene_manager(&p_game->scene_manager);
    PLATFORM_establish_scenes(
            &p_game->scene_manager);
    p_game->is_world__initialized = false;
    p_game->m_game_action_handler = m_game_action_handler;
}

int run_game(Game *p_game) {
    if (!p_game->scene_manager.p_active_scene) {
        debug_abort("Active scene not established.");
        debug_warning("PLATFORM_establish_scenes, did you forget to implement?");
        return -1;
    }
    Scene_Manager *p_scene_manager =
        &p_game->scene_manager;
    Scene *p_active_scene;
    while ((p_active_scene =
            get_p_active_scene_from__scene_manager(
                p_scene_manager))) {
#ifndef NDEBUG
    debug_info("TRANSITION p_active_scene -> %p",
            p_active_scene);
#endif
        p_active_scene =
            p_game->scene_manager.p_active_scene;
#ifndef NDEBUG
        debug_info("loading scene.");
#endif
        p_active_scene->m_load_scene_handler(
                p_active_scene,
                p_game);
#ifndef NDEBUG
        debug_info("entering scene.");
#endif
        p_active_scene->m_enter_scene_handler(
                p_active_scene,
                p_game);
#ifndef NDEBUG
        debug_info("unloading scene.");
#endif
        p_active_scene->m_unload_scene_handler(
                p_active_scene,
                p_game);
    }
#ifndef NDEBUG
    debug_info("p_active_scene == 0");
    debug_info("Game stopped.");
#endif
    return 0;
}

void manage_game(Game *p_game) {
    manage_game__pre_render(p_game);
    manage_game__post_render(p_game);
    loop_timer_u32(&p_game->tick__timer_u32);
}

void manage_game__pre_render(Game *p_game) {
    PLATFORM_pre_render(p_game);
}

void manage_game__post_render(Game *p_game) {
    PLATFORM_poll_input(&p_game->input);
    poll_ui_manager__update(&p_game->ui_manager, p_game);

    PLATFORM_post_render(p_game);
}
