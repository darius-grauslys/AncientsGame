#ifndef NDS_GAME_H
#define NDS_GAME_H

#include "game.h"
#include "rendering/gfx_context.h"

static inline
UI_Manager *NDS_get_p_ui_manager_from__game(
        Game *p_game) {
    return NDS_get_p_ui_manager_from__PLATFORM_gfx_context(
            get_p_PLATFORM_gfx_context_from__game(
                p_game));
}
#endif
