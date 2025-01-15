#ifndef SDL_GFX_WINDOW_MANAGER_H
#define SDL_GFX_WINDOW_MANAGER_H

#include "defines.h"
#include "defines_weak.h"
#include "sdl_defines.h"

void SDL_initialize_gfx_window_manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager);

PLATFORM_Graphics_Window *SDL_allocate_PLATFORM_gfx_window_from__manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager);

void SDL_release_PLATFORM_gfx_window_from__manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

PLATFORM_Graphics_Window *SDL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera,
        Texture_Flags texture_flags);

void SDL_release_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

#endif
