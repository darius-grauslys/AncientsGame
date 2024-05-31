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

#include <entity/controllers/collidable_entity_handlers.h>
#include <entity/controllers/entity_handlers.h>
#include <entity/controllers/controller_player.h>
#include <entity/controllers/controller_dummy.h>
#include <entity/controllers/humanoid_animation_handler.h>

#include <collisions/hitbox_aabb.h>
#include <collisions/collision_manager.h>

#include <world/chunk.h>
#include <world/tile.h>

#include <ui/ui_manager.h>

void init_game(
        Game *p_game,
        m_Game_Action_Handler m_game_action_handler) {
    PLATFORM_init_gfx_context(&p_game->gfx_context);
    init_ui_manager(&p_game->ui_manager);
    init_scene_manager(&p_game->scene_manager);
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
            get_active_scene_ptr_from__scene_manager(
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
    p_game->tick__timer_u32++;
}

void manage_game__pre_render(Game *p_game) {
    PLATFORM_pre_render(p_game);
}

void manage_game__post_render(Game *p_game) {
    PLATFORM_poll_input(&p_game->input);
    poll_ui_manager__update(&p_game->ui_manager, p_game);

    PLATFORM_post_render(p_game);
}
