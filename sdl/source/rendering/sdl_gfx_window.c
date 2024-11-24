#include "defines_weak.h"
#include "game.h"
#include "rendering/sdl_sprite.h"
#include "sdl_defines.h"
#include <rendering/sdl_gfx_window.h>

void SDL_initialize_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    p_PLATFORM_gfx_window
        ->p_PLATFORM_gfx_context =
        p_PLATFORM_gfx_context
        ;
    // TODO: initialize texture as deallocated
    p_PLATFORM_gfx_window
        ->p_SDL_graphics_window__data = 0;
    p_PLATFORM_gfx_window
        ->is_allocated = false;
}

void SDL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {

    f_SDL_Allocate_Gfx_Window f_SDL_allocate_gfx_window =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_allocate_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_allocate_gfx_window, f_SDL_allocate_gfx_window == 0.");
        return;
    }
#endif

    f_SDL_allocate_gfx_window(
            p_PLATFORM_gfx_context,
            p_PLATFORM_gfx_window,
            p_texture_allocation_specification);
}

void SDL_release_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {

    f_SDL_Release_Gfx_Window f_SDL_release_gfx_window =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_release_gfx_window
        ;

#ifndef NDEBUG
    if (!f_SDL_release_gfx_window) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_release_gfx_window, f_SDL_release_gfx_window == 0.");
        return;
    }
#endif

    f_SDL_release_gfx_window(
            p_PLATFORM_gfx_context,
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
