#include "defines_weak.h"
#include <SDL2/SDL_render.h>
#include <defines.h>
#include <rendering/sdl_gfx_context.h>
#include <sdl_defines.h>

PLATFORM_Gfx_Context __SDL_Gfx_Context;

void SDL_initialize_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        SDL_Window *p_SDL_window) {
    p_PLATFORM_gfx_context
        ->p_SDL_renderer =
        SDL_CreateRenderer(
                p_SDL_window,
                -1, 
                0);
    p_PLATFORM_gfx_context
        ->graphics_window__main_window
        .p_SDL_renderer =
        p_PLATFORM_gfx_context
        ->p_SDL_renderer;
    p_PLATFORM_gfx_context
        ->p_SDL_window =
        p_SDL_window;
}
