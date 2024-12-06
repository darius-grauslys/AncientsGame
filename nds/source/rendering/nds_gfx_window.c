#include "rendering/nds_gfx_window.h"
#include "defines_weak.h"
#include "rendering/gfx_context.h"
#include "vectors.h"

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

void PLATFORM_set_gfx_window__position(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Vector__3i32 position_of__window) {
    if (!NDS_is_PLATFORM_gfx_window_associated_with_a__background(
                p_PLATFORM_gfx_window)) {
        return;
    }
    NDS_Background *p_NDS_background =
        NDS_get_p_background_of__PLATFORM_gfx_window(
                p_PLATFORM_gfx_window);
    p_NDS_background
        ->current_position__3i32 = position_of__window;
    bgSetScroll(
            p_NDS_background
            ->background_index_from__hardware, 
            p_NDS_background->current_position__3i32.x__i32, 
            -p_NDS_background->current_position__3i32.y__i32); 
}

///
/// Returns the position of the PLATFORM_gfx_window at time of allocation.
///
Vector__3i32 PLATFORM_get_gfx_window__origin(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    if (NDS_is_PLATFORM_gfx_window_associated_with_a__background(
                p_PLATFORM_gfx_window)) {
        return NDS_get_p_background_of__PLATFORM_gfx_window(
                p_PLATFORM_gfx_window)
            ->starting_position__3i32;
    }

    return VECTOR__3i32__OUT_OF_BOUNDS;
}

Vector__3i32 PLATFORM_get_gfx_window__position(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    if (NDS_is_PLATFORM_gfx_window_associated_with_a__background(
                p_PLATFORM_gfx_window)) {
        return NDS_get_p_background_of__PLATFORM_gfx_window(
                p_PLATFORM_gfx_window)
            ->current_position__3i32;
    }

    return VECTOR__3i32__OUT_OF_BOUNDS;
}

Game_Action PLATFORM_get_gfx_window__game_action(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return p_PLATFORM_gfx_window
        ->associated_game_action;
}
