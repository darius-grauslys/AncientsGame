#include "game.h"
#include "input/input.h"
#include "platform_defines.h"
#include "rendering/nds_gfx_context.h"
#include "scene/scene_manager.h"
#include <scene/scene__main_menu.h>
#include <debug/nds_debug.h>

void m_load_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_enter_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

void init_scene_as__main_menu(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__main_menu_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__main_menu_handler;
    p_scene->m_unload_scene_handler =
        m_unload_scene_as__main_menu_handler;
}

void m_load_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_init_gfx_for__main_menu(
            &p_game->gfx_context);
}

void m_enter_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    while (1) {
        debug_info("I am in main menu.");
        manage_game(p_game);
        if (is_input__forward_held(&p_game->input)) {
            p_game->scene_manager.p_active_scene = 0;
            break;
        }
    }
}

void m_unload_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    debug_info("I am leaving main menu");
    p_game->scene_manager.p_active_scene =
        get_scene_ptr_from__scene_manager(
                &p_game->scene_manager, 
                SCENE_IDENTIFIER__GAME);
}
