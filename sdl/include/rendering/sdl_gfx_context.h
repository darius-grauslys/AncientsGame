#ifndef SDL_GFX_CONTEXT_H
#define SDL_GFX_CONTEXT_H

#include "defines_weak.h"
#include <SDL2/SDL_video.h>

extern PLATFORM_Gfx_Context __SDL_Gfx_Context;

void SDL_initialize_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        SDL_Window *p_SDL_window);

#endif
