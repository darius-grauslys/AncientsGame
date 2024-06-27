#ifndef NDS_UI__MENU__SINGLEPLAYER_H
#define NDS_UI__MENU__SINGLEPLAYER_H

#include <defines_weak.h>

UI_Element *NDS_allocate_ui_for__ui_window__singleplayer(
        Game *p_game);

void NDS_set_ui_background_to__menu_single_player(
        PLATFORM_Gfx_Context *p_gfx_context);

#endif
