#ifndef SDL_SPRITE_MANAGER_H
#define SDL_SPRITE_MANAGER_H

#include "defines_weak.h"
#include <sdl_defines.h>

void SDL_initialize_sprite_manager(
        SDL_Sprite_Manager *p_SDL_sprite_manager);

///
/// DO NOT INVOKE. This is internal.
///
PLATFORM_Sprite *SDL_allocate_sprite_with__sprite_manager(
        SDL_Sprite_Manager *p_SDL_sprite_manager);

///
/// DO NOT INVOKE. This is internal.
///
void SDL_release_sprite_from__sprite_manager(
        SDL_Sprite_Manager *p_SDL_sprite_manager,
        PLATFORM_Sprite *p_PLATFORM_sprite);

void SDL_dispose_sprite_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        SDL_Sprite_Manager *p_SDL_sprite_manager);

#endif
