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

///
/// Returns -1 if the quantity of windows for the given kind
/// exceed that of the p_PLATFORM_gfx_windows ptr_buffer size.
///
/// Otherwise returns the amount of windows found in a
/// non-deterministic order.
///
/// NOTE: Specify UI_Window_Kind__Unknown to get all windows.
///
Signed_Quantity__i32 SDL_get_p_PLATFORM_gfx_windows_by__type_from__manager(
        SDL_Gfx_Window_Manager *p_SDL_gfx_window_manager,
        UI_Window_Kind the_kind_of__window_to__get,
        PLATFORM_Graphics_Window **p_PLATFORM_gfx_windows,
        Quantity__u32 size_of__ptr_buffer);

#endif
