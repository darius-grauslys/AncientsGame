#include "ui/sdl_ui.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_gfx_window.h"
#include "rendering/texture.h"

///
/// Opens the specified UI. Depending on the backend this
/// might close all other UI's.
///
void PLATFORM_open_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__open,
        Game_Action *p_game_action) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__ui =
        SDL_get_graphics_window__ui_from__gfx_contexT(
                p_PLATFORM_gfx_context);

    if (SDL_is_gfx_window__allocated(
                p_PLATFORM_gfx_window__ui)) {
        if (SDL_is_gfx_window_of__this_ui_window_kind(
                    p_PLATFORM_gfx_window__ui, 
                    the_kind_of__ui_window_to__open)) {
            debug_warning("SDL::PLATFORM_open_ui, redundant opening of UI_Window_Kind.");
            return;
        }

        SDL_release_gfx_window(
                p_PLATFORM_gfx_context, 
                p_PLATFORM_gfx_window__ui);
    }

    Texture_Allocation_Specification texture_alloc_spec;

    initialize_texture_allocation_specification(
            &texture_alloc_spec, 
            TEXTURE_FLAG__SIZE_512x512, 
            SDL_get_main_graphics_window_from__gfx_context(
                p_PLATFORM_gfx_context));

    SDL_allocate_gfx_window(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_gfx_window__ui, 
            &texture_alloc_spec);

    UI_Tile_Map__Wrapper ui_tile_map__wrapper =
        p_PLATFORM_gfx_window__ui
        ->SDL_graphics_window__ui_tile_map__wrapper;

    //TODO: remove
    for (int y=8;y<16+8;y++) {
        for (int x=8;x<16+8;x++) {
            ui_tile_map__wrapper.p_ui_tile_data[
                x
                + y * ui_tile_map__wrapper.width_of__ui_tile_map] =
                5;
        }
    }

    SDL_compose_gfx_window(
            p_game,
            p_PLATFORM_gfx_window__ui);

    debug_info("SDL::PLATFORM_open_ui, ui opened.");
}

void PLATFORM_refresh_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__open) {
    // TODO: impl
}

void PLATFORM_update_ui(
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__ui =
        SDL_get_graphics_window__ui_from__gfx_contexT(
                p_PLATFORM_gfx_context);

    if (!SDL_is_gfx_window__allocated(
                p_PLATFORM_gfx_window__ui)) {
        return;
    }
    
    SDL_render_gfx_window(
            p_game, 
            p_PLATFORM_gfx_window__ui);
}

///
/// Closes the specified UI. Depending on the backend this
/// might cause a UI window to open. For example, on NDS
/// this will close the specified UI Window, and transition
/// to the UI Idle window.
///
void PLATFORM_close_ui(
        Game *p_game,
        enum UI_Window_Kind the_kind_of__ui_window_to__close) {
    //TODO: prop impl, with ui window manager

    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(
                p_game);

    PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__ui =
        SDL_get_graphics_window__ui_from__gfx_contexT(
                p_PLATFORM_gfx_context);

    if (!SDL_is_gfx_window__allocated(
                p_PLATFORM_gfx_window__ui)) {
        return;
    }

    if (SDL_is_gfx_window_of__this_ui_window_kind(
                p_PLATFORM_gfx_window__ui, 
                the_kind_of__ui_window_to__close)) {
        SDL_release_gfx_window(
                p_PLATFORM_gfx_context, 
                p_PLATFORM_gfx_window__ui);
    }

    debug_info("SDL::PLATFORM_open_ui, ui closed.");
}

enum UI_Window_Kind PLATFORM_get_last_opened_ui(void) {
    // TODO: impl
    return UI_Window_Kind__None;
}

Quantity__u8 PLATFORM_get_all_opened_ui(
        enum UI_Window_Kind *p_ui_window_kind__buffer,
        Quantity__u8 size_of__buffer) {
    // TODO: impl
    return 0;
}
