#ifndef NDS_UI__MENU_H
#define NDS_UI__MENU_H

#include <defines_weak.h>

void m_main_menu__singleplayer_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game);

void m_main_menu__multiplayer_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game);

void m_main_menu__settings_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game);

void m_main_menu__play_button__clicked_handler(
        UI_Element *p_this_button,
        Game *p_game);

#endif
