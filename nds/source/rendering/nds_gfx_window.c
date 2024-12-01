#include "rendering/nds_gfx_window.h"
#include "defines_weak.h"
#include "rendering/gfx_context.h"

void NDS_initialize_gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        NDS_Background *p_NDS_background_associated_to__this_window,
        OamState *p_oam_state) {
    p_PLATFORM_gfx_window->p_PLATFORM_gfx_context =
        p_PLATFORM_gfx_context;
    p_PLATFORM_gfx_window->p_oam_state =
        p_oam_state;
    p_PLATFORM_gfx_window->p_NDS_background_associated_to__this_window =
        p_NDS_background_associated_to__this_window;
    //TODO: empty game_action
}

UI_Tile_Map__Wrapper PLATFORM_get_tile_map__wrapper_from__gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    // TODO: impl
    debug_abort("NDS::PLATFORM_get_tile_map__wrapper_from__gfx_window NOT IMPL");
    return (UI_Tile_Map__Wrapper){};
}

UI_Manager *PLATFORM_get_p_ui_manager_from__gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return NDS_get_p_ui_manager_from__PLATFORM_gfx_context(
            p_PLATFORM_gfx_window
            ->p_PLATFORM_gfx_context);
}
