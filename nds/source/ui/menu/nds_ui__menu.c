#include <ui/menu/nds_ui__menu.h>
#include <defines.h>
#include <scene/scene_manager.h>

void m_main_menu__singleplayer_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game) {
    set_p_active_scene_for__scene_manager(
            &p_game->scene_manager, 
            SCENE_IDENTIFIER__SINGLE_PLAYER_MENU);
}

void m_main_menu__multiplayer_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game) {
    set_p_active_scene_for__scene_manager(
            &p_game->scene_manager, 
            SCENE_IDENTIFIER__MULTIPLAYER_MENU);
}

void m_main_menu__settings_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game) {
    set_p_active_scene_for__scene_manager(
            &p_game->scene_manager, 
            SCENE_IDENTIFIER__SETTINGS_MENU);
}

void m_main_menu__play_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game) {
    set_p_active_scene_for__scene_manager(
            &p_game->scene_manager, 
            SCENE_IDENTIFIER__GAME);
}
