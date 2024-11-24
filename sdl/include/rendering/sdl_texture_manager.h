#ifndef SDL_TEXTURE_MANAGER_H
#define SDL_TEXTURE_MANAGER_H

#include "platform.h"
#include <sdl_defines.h>

void SDL_initialize_texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager);

PLATFORM_Texture *SDL_allocate_texture_with__texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager);

PLATFORM_Texture *SDL_get_texture_from__texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager,
        SDL_Texture_String__Const p_SDL_texture_string);

void SDL_release_texture_from__texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager,
        PLATFORM_Texture *p_PLATFORM_texture);

void SDL_dispose_texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager);

#endif
