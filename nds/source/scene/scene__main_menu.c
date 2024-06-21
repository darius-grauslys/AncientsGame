#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/reserves.h"
#include "game.h"
#include "input/input.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/nds_gfx_context.h"
#include "rendering/sprite.h"
#include "ui/menu/nds_ui__menu__main.h"
#include <scene/scene__main_menu.h>
#include <debug/nds_debug.h>
#include <scene/scene.h>

void m_load_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_initialize_gfx_for__main_menu(
            &p_game->gfx_context);
    NDS_initialize_gfx_for__ui(
            &p_game->gfx_context);
    NDS_set_ui_manager_to__menu(
            &p_game->ui_manager);
    NDS_set_ui_background_to__menu_main(
            &p_game->gfx_context);
}

void initialize_scene_as__main_menu(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__main_menu_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler__default;
}
