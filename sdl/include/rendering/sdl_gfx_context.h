#ifndef SDL_GFX_CONTEXT_H
#define SDL_GFX_CONTEXT_H

#include "defines_weak.h"
#include "rendering/sdl_gfx_window.h"
#include "sdl_defines.h"

extern PLATFORM_Gfx_Context __SDL_Gfx_Context;

void SDL_initialize_gfx_context(
        Game *p_game,
        SDL_Gfx_Sub_Context__Kind the_kind_of__sub_context);

void SDL_dispose_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

void SDL_clear_screen(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

static inline
SDL_Sprite_Manager *SDL_get_p_sprite_manager_from__gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 
        &p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .SDL_sprite_manager
        ;
}

static inline
SDL_Texture_Manager *SDL_get_p_texture_manager_from__gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return 
        &p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .SDL_texture_manager
        ;
}

static inline
PLATFORM_Graphics_Window *SDL_get_main_graphics_window_from__gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &p_PLATFORM_gfx_context->SDL_graphics_window__main;
}

static inline
UI_Tile_Map_Manager *SDL_get_p_ui_tile_map_manager_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &p_PLATFORM_gfx_context
        ->SDL_ui_tile_map_manager;
}

static inline
SDL_Gfx_Window_Manager *SDL_get_p_gfx_window_manager_from__PLATFORM_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context) {
    return &p_PLATFORM_gfx_context
        ->SDL_gfx_window_manager;
}

#endif
