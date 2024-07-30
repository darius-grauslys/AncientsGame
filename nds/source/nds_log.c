#include "defines_weak.h"
#include "game.h"
#include "rendering/gfx_context.h"
#include "ui/nds_ui__log.h"
#include "ui/ui_window.h"
#include <platform.h>

// TODO: all logs write to same background currently
bool PLATFORM_update_log__global(Game *p_game) {
    if (!is_ui_window_kind_of__this_kind(
                get_the_kind_of__active_ui_window(
                    get_p_PLATFORM_gfx_context_from__game(p_game)), 
                UI_Window_Kind__Idle)) {
        return false;
    }

    NDS_update_log(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            get_p_log__global_from__game(p_game));
}

bool PLATFORM_update_log__local(Game *p_game) {
    if (!is_ui_window_kind_of__this_kind(
                get_the_kind_of__active_ui_window(
                    get_p_PLATFORM_gfx_context_from__game(p_game)), 
                UI_Window_Kind__Idle)) {
        return false;
    }

    NDS_update_log(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            get_p_log__local_from__game(p_game));
}

bool PLATFORM_update_log__system(Game *p_game) {
    if (!is_ui_window_kind_of__this_kind(
                get_the_kind_of__active_ui_window(
                    get_p_PLATFORM_gfx_context_from__game(p_game)), 
                UI_Window_Kind__Idle)) {
        return false;
    }

    NDS_update_log(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            get_p_log__system_from__game(p_game));
}

bool PLATFORM_clear_log__global(Game *p_game) {
    if (!is_ui_window_kind_of__this_kind(
                get_the_kind_of__active_ui_window(
                    get_p_PLATFORM_gfx_context_from__game(p_game)), 
                UI_Window_Kind__Idle)) {
        return false;
    }

    NDS_clear_log(
            get_p_PLATFORM_gfx_context_from__game(p_game));
}

bool PLATFORM_clear_log__local(Game *p_game) {
    if (!is_ui_window_kind_of__this_kind(
                get_the_kind_of__active_ui_window(
                    get_p_PLATFORM_gfx_context_from__game(p_game)), 
                UI_Window_Kind__Idle)) {
        return false;
    }

    NDS_clear_log(
            get_p_PLATFORM_gfx_context_from__game(p_game));
}

bool PLATFORM_clear_log__system(Game *p_game) {
    if (!is_ui_window_kind_of__this_kind(
                get_the_kind_of__active_ui_window(
                    get_p_PLATFORM_gfx_context_from__game(p_game)), 
                UI_Window_Kind__Idle)) {
        return false;
    }

    NDS_clear_log(
            get_p_PLATFORM_gfx_context_from__game(p_game));
}
