#include "defines_weak.h"
#include "game.h"
#include "ui/ui_button.h"
#include "ui/ui_manager.h"
#include <ui/handlers/hud/nds_ui_handler__hud_button.h>
#include <ui/game/nds_ui_window__game__hud.h>
#include "nds_game.h"

void m_NDS_ui_button__clicked_handler__hud(
        UI_Element *p_this_button,
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    Index__u32 index_of__this_button =
        get_index_of__p_ui_element_in__ui_manager(
                NDS_get_p_ui_manager_from__game(p_game), 
                p_this_button)
        - NDS_UI_WINDOW__GAME__HUD_P_HUD_BUTTONS_0;

    switch (index_of__this_button) {
        default:
            break;
        case 0:
            PLATFORM_open_ui(
                    p_game,
                    (toggle_ui_button(p_this_button))
                        ? UI_Window_Kind__Equip
                        : UI_Window_Kind__Idle,
                    0);
            break;
        case 1:
            PLATFORM_open_ui(
                    p_game,
                    (toggle_ui_button(p_this_button))
                        ? UI_Window_Kind__Trade
                        : UI_Window_Kind__Idle,
                    0);
            break;
        case 2:
            PLATFORM_open_ui(
                    p_game,
                    (toggle_ui_button(p_this_button))
                        ? UI_Window_Kind__Labor
                        : UI_Window_Kind__Idle,
                    0);
            break;
    }
}
