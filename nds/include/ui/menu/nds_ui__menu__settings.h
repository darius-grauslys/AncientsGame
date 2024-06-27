#ifndef NDS_UI__MENU__SETTINGS_H
#define NDS_UI__MENU__SETTINGS_H

#include "defines_weak.h"

UI_Element *NDS_allocate_ui_for__ui_window__settings(
        Game *p_game);

void NDS_set_ui_manager_to__settings(
        UI_Manager *p_ui_manager);

void NDS_set_ui_background_to__menu_settings(
        PLATFORM_Gfx_Context *p_gfx_context);

#endif
