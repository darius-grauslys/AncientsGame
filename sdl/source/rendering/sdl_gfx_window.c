#include "defines_weak.h"
#include <rendering/sdl_gfx_window.h>

void SDL_initialize_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        void *p_SDL_gfx_window__data) {
    p_PLATFORM_gfx_window
        ->p_PLATFORM_gfx_context =
        p_PLATFORM_gfx_context;
    p_PLATFORM_gfx_window
        ->p_SDL_graphics_window__data =
        p_SDL_gfx_window__data;
}
