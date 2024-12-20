#ifndef SDL_GFX_WINDOW_H
#define SDL_GFX_WINDOW_H

#include "defines_weak.h"
#include <sdl_defines.h>

void SDL_initialize_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

void SDL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

void SDL_release_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

void SDL_render_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

static inline
bool SDL_is_gfx_window__allocated(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return p_PLATFORM_gfx_window
        ->is_allocated
        ;
}

static inline
void SDL_set_gfx_window_as__allocated(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    p_PLATFORM_gfx_window
        ->is_allocated = true;
}

static inline
void SDL_set_gfx_window_as__deallocated(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    p_PLATFORM_gfx_window
        ->is_allocated = false;
}

#endif
