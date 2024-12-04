#ifndef SDL_GFX_WINDOW_H
#define SDL_GFX_WINDOW_H

#include "defines.h"
#include "defines_weak.h"
#include "vectors.h"
#include <sdl_defines.h>

void SDL_initialize_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Camera *p_camera,
        UI_Window_Kind the_kind_of__ui_window,
        Vector__3i32F4 position_of__graphics_window__3i32F4);

void SDL_compose_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

void SDL_render_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window);

static inline
void SDL_initialize_gfx_window_as__deallocated(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    SDL_initialize_gfx_window(
            0, 
            p_PLATFORM_gfx_window,
            0,
            UI_Window_Kind__None,
            VECTOR__3i32F4__OUT_OF_BOUNDS);
}

static inline
bool SDL_is_gfx_window__allocated(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return 
        p_PLATFORM_gfx_window
        && p_PLATFORM_gfx_window
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

static inline
UI_Window_Kind SDL_get_ui_window_kind_of__gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return p_PLATFORM_gfx_window
        ->the_kind_of__ui_window;
}

static inline
void SDL_set_position_of__gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Vector__3i32F4 position_of__gfx_window) {
    p_PLATFORM_gfx_window
        ->SDL_position_of__graphics_window =
        position_of__gfx_window;
}

static inline
Vector__3i32F4 SDL_get_position_of__gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return p_PLATFORM_gfx_window
        ->SDL_position_of__graphics_window;
}

static inline
UI_Manager *SDL_get_p_ui_manager_from__PLATFORM_gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return &p_PLATFORM_gfx_window
        ->SDL_graphics_window__ui_manager;
}

static inline
UI_Tile_Map__Wrapper SDL_get_tile_map__wrapper_from__PLATFORM_gfx_window(
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window) {
    return p_PLATFORM_gfx_window
        ->SDL_graphics_window__ui_tile_map__wrapper;
}

#endif
