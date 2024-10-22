#ifndef NDS_GRAPHICS_WINDOW_H
#define NDS_GRAPHCIS_WINDOW_H

#include <nds_defines.h>

static inline
void NDS_copy_game_action_into__sub_graphics_window(
        Game *p_game,
        Game_Action *p_game_action) {
    p_game
        ->p_PLATFORM_gfx_context
        ->graphics_window__sub
        .associated_game_action = *p_game_action;
}

static inline
Game_Action *NDS_get_p_copy_of__associated_game_action_of__sub_graphics_window(
        Game *p_game) {
    return &p_game
        ->p_PLATFORM_gfx_context
        ->graphics_window__sub
        .associated_game_action
        ;
}

#endif
