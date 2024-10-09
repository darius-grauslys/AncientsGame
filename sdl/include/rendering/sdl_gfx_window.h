#ifndef SDL_GFX_WINDOW_H
#define SDL_GFX_WINDOW_H

#include "defines_weak.h"
#include <sdl_defines.h>

void SDL_initialize_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        void *p_SDL_gfx_window__data);

#endif
