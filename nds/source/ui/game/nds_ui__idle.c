#include "ui/nds_ui.h"
#include <ui/game/nds_ui__idle.h>
#include <ui/game/nds_ui__hud.h>

UI_Element *NDS_allocate_ui_for__ui_window__idle(
        Game *p_game) {
    NDS_allocate_ui_for__game_hud(p_game);
}

void NDS_set_ui_background_to__idle(
        PLATFORM_Gfx_Context *p_gfx_context) {

}
