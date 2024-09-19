#include "defines_weak.h"
#include "inventory/inventory_manager.h"
#include "inventory/item_manager.h"
#include "log/log.h"
#include "platform.h"
#include "platform_defines.h"
#include "process/process_manager.h"
#include "random.h"
#include "scene/scene_manager.h"
#include "sort/sort_list/sort_list_manager.h"
#include "world/path_finding/path_list_manager.h"
#include <game.h>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <debug/debug.h>
#include <input/input.h>
#include <world/chunk_manager.h>
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
    initialize_repeatable_psuedo_random(
            &p_game->repeatable_pseudo_random, 
            (u32)p_game);
    initialize_scene_manager(&p_game->scene_manager);
    initialize_process_manager(
            get_p_process_manager_from__game(p_game));
    initialize_sort_list_manager(
            get_p_sort_list_manager_from__game(p_game));
    initialize_path_list_manager(
            get_p_path_list_manager_from__game(p_game));
    initialize_inventory_manager(
            get_p_inventory_manager_from__game(p_game));
    initialize_item_manager(
            get_p_item_manager_from__game(p_game));
    load_core_items_into__item_manager(
            get_p_item_manager_from__game(p_game));

    initialize_log(get_p_log__global_from__game(p_game));
    initialize_log(get_p_log__local_from__game(p_game));
    initialize_log(get_p_log__system_from__game(p_game));

    p_game->is_world__initialized = false;
    p_game->m_game_action_handler = m_game_action_handler;
}

bool print_log__global(Game *p_game, char *cstr) {
    bool result = put_cstr_into__message(
            get_next_p_message_in__log(
                get_p_log__global_from__game(p_game)), 
            cstr);
    PLATFORM_update_log__global(p_game);
    flush_message_into__log(get_p_log__global_from__game(p_game));
    return result;
}

bool print_log__local(Game *p_game, char *cstr) {
    bool result = put_cstr_into__message(
            get_next_p_message_in__log(
                get_p_log__local_from__game(p_game)), 
            cstr);
    PLATFORM_update_log__local(p_game);
    flush_message_into__log(get_p_log__local_from__game(p_game));
    return result;
}

bool print_log__system(Game *p_game, char *cstr) {
    bool result = put_cstr_into__message(
            get_next_p_message_in__log(
                get_p_log__system_from__game(p_game)), 
            cstr);
    PLATFORM_update_log__system(p_game);
    flush_message_into__log(get_p_log__system_from__game(p_game));
    return result;
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
        debug_info("TRANSITION p_active_scene -> %p",
                p_active_scene);
        p_active_scene =
            p_game->scene_manager.p_active_scene;
        debug_info("loading scene.");
        if (p_active_scene->m_load_scene_handler)
            p_active_scene->m_load_scene_handler(
                    p_active_scene,
                    p_game);
        debug_info("entering scene.");
        if (!p_active_scene->m_enter_scene_handler) {
            debug_error("p_active_scene->m_enter_scene_handler is null.");
            set_p_active_scene_for__scene_manager(
                    p_scene_manager, 
                    SCENE_IDENTIFIER__MAIN_MENU);
            continue;
        }
        p_active_scene->m_enter_scene_handler(
                p_active_scene,
                p_game);
        debug_info("unloading scene.");
        if (p_active_scene->m_unload_scene_handler)
            p_active_scene->m_unload_scene_handler(
                    p_active_scene,
                    p_game);
    }
    debug_info("p_active_scene == 0");
    debug_info("Game stopped.");
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
    poll_process_manager(
            get_p_process_manager_from__game(p_game), p_game);
    poll_ui_manager__update(
            get_p_ui_manager_from__game(p_game), p_game);
    PLATFORM_poll_audio_effects(
            get_p_PLATFORM_audio_context_from__game(p_game));

    PLATFORM_post_render(p_game);
}
