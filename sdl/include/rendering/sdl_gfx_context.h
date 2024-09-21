#ifndef SDL_GFX_CONTEXT_H
#define SDL_GFX_CONTEXT_H

#include "defines_weak.h"
#include <SDL2/SDL_video.h>

extern PLATFORM_Gfx_Context __SDL_Gfx_Context;

typedef enum {
    SDL_Gfx_Sub_Context__None,
    SDL_Gfx_Sub_Context__OpenGL_1_2,
    SDL_Gfx_Sub_Context__OpenGL_3_0,
    SDL_Gfx_Sub_Context__Vulcan //TODO: not impl'd
} SDL_Gfx_Sub_Context__Kind;

void SDL_initialize_gfx_context(
        Game *p_game,
        SDL_Gfx_Sub_Context__Kind the_kind_of__sub_context);

void SDL_dispose_gfx_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

void SDL_clear_screen(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

#endif
