#include "debug/debug.h"
#include "defines.h"
#include "nds_defines.h"
#include "defines_weak.h"
#include "entity/reserves.h"
#include "game.h"
#include "input/input.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/sprite.h"
#include "ui/menu/nds_ui_window__menu__main.h"
#include <scene/nds_scene__main_menu.h>
#include <debug/nds_debug.h>
#include <scene/scene.h>
#include <rendering/gfx_context.h>

void m_load_scene_as__main_menu_handler(
        Scene *p_this_scene,
        Game *p_game) {
    NDS_set_video_modes_to__MODE_0_2D();
    NDS_initialize_gfx_for__ui(
            p_game->p_PLATFORM_gfx_context);
    // TODO: re-impl
    // NDS_set_ui_background_to__menu_main(
    //         &p_game->gfx_context);
    PLATFORM_open_ui(
            p_game,
            UI_Window_Kind__Main_Menu);
}

void initialize_scene_as__main_menu(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__main_menu_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler__default;
}
