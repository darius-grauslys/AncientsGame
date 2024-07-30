#include "ui/nds_ui__idle.h"
#include "game.h"
#include "nds/arm9/background.h"
#include "ui/game/nds_ui_window__game__idle.h"
#include "ui/nds_ui__log.h"
#include "nds_defines.h"

void NDS_open_ui__idle(
        Game *p_game) {
    NDS_initialize_log(
            get_p_PLATFORM_gfx_context_from__game(p_game));

    NDS_allocate_ui_for__nds_ui_window__game__idle(p_game);
}
