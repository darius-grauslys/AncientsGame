#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include "defines_weak.h"
#include <sdl_defines.h>

void SDL_update_texture_format_and__access(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

static inline
bool SDL_is_texture__allocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return p_PLATFORM_texture->SDL_is_texture__allocated;
}

static inline
void SDL_set_texture_as__allocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    p_PLATFORM_texture->SDL_is_texture__allocated = true;
}

static inline
void SDL_set_texture_as__deallocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    p_PLATFORM_texture->SDL_is_texture__allocated = false;
}

#endif
