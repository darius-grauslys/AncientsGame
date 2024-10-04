#ifndef SDL_GFX_CONTEXT_H
#define SDL_GFX_CONTEXT_H

#include "defines_weak.h"
#include "sdl_defines.h"
#include <SDL2/SDL_video.h>

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
void SDL_set_active_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    p_PLATFORM_gfx_context->p_active_camera =
        p_camera;
}

#endif
