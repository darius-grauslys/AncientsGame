#ifndef SDL_RENDER_WORLD_H
#define SDL_RENDER_WORLD_H

#include "sdl_defines.h"

void SDL_render_world(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world);

void f_SDL_render_world__default(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world);

#endif
