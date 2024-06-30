#include <ui/menu/nds_ui_window__menu__singleplayer.h>
#include <ui/nds_ui.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
// THIS CODE IS AUTO GENERATED. Go to ./nds/assets/ui/xml/ instead of modifying this file.

UI_Element *NDS_allocate_ui_for__nds_ui_window__menu__singleplayer(Game *p_game){
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    UI_Element *p_button__singleplayer = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button__singleplayer, m_ui_button__clicked_handler__default);
    set_ui_element__hitbox(p_button__singleplayer, 80, 24, get_vector__3i32(12 + 0, 60 + 0, 0));

    UI_Element *p_button__multiplayer = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button__multiplayer, m_ui_button__clicked_handler__default);
    set_ui_element__hitbox(p_button__multiplayer, 80, 24, get_vector__3i32(12 + 0, 104 + 0, 0));

    UI_Element *p_button__settings = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button__settings, m_ui_button__clicked_handler__default);
    set_ui_element__hitbox(p_button__settings, 80, 24, get_vector__3i32(12 + 0, 148 + 0, 0));

    UI_Element *p_button__play = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button__play, m_ui_button__clicked_handler__default);
    set_ui_element__hitbox(p_button__play, 104, 96, get_vector__3i32(132 + 0, 68 + 0, 0));
}
