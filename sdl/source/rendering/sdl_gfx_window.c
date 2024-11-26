#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_sprite.h"
#include "rendering/texture.h"
#include "sdl_defines.h"
#include "ui/ui_manager.h"
#include "ui/ui_tile_map_manager.h"
#include <rendering/sdl_gfx_window.h>

void SDL_initialize_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        UI_Window_Kind the_kind_of__ui_window,
        Vector__3i32F4 position_of__graphics_window__3i32F4) {
    p_PLATFORM_gfx_window
        ->p_PLATFORM_gfx_context =
        p_PLATFORM_gfx_context
        ;

    initialize_ui_manager(
            SDL_get_p_ui_manager_from__PLATFORM_gfx_window(
                p_PLATFORM_gfx_window),
            p_PLATFORM_gfx_window);

    // TODO: initialize texture as deallocated
    p_PLATFORM_gfx_window
        ->p_SDL_graphics_window__data = 0;
    p_PLATFORM_gfx_window
        ->is_allocated = false;
    p_PLATFORM_gfx_window
        ->the_kind_of__ui_window =
        the_kind_of__ui_window;
    p_PLATFORM_gfx_window
        ->SDL_position_of__graphics_window =
        position_of__graphics_window__3i32F4;
}

void SDL_compose_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    f_SDL_Compose_Gfx_Window f_SDL_compose_gfx_window =
        get_p_PLATFORM_gfx_context_from__game(
                p_game)
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_compose_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_compose_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_compose_gfx_window, f_SDL_render_gfx_window == 0.");
        return;
    }
#endif

    f_SDL_compose_gfx_window(
            p_game,
            p_PLATFORM_gfx_window);
}

void SDL_render_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {

    f_SDL_Render_Gfx_Window f_SDL_render_gfx_window =
        get_p_PLATFORM_gfx_context_from__game(
                p_game)
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_render_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_render_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_render_gfx_window, f_SDL_render_gfx_window == 0.");
        return;
    }
#endif

    f_SDL_render_gfx_window(
            p_game,
            p_PLATFORM_gfx_window);
}

UI_Manager *PLATFORM_get_p_ui_manager_from__gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return SDL_get_p_ui_manager_from__PLATFORM_gfx_window(
            p_PLATFORM_gfx_window);
}
