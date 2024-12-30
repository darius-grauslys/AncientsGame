#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include "defines_weak.h"
#include <sdl_defines.h>
#include "rendering/texture.h"

void SDL_initialize_texture_as__deallocated(
        PLATFORM_Texture *p_PLATFORM_texture);

void SDL_update_texture_format_and__access(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Flags texture_flags);

static inline
bool SDL_is_texture__allocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return is_texture_flags__allocated(
            *PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
                p_PLATFORM_texture));
}

static inline
void SDL_set_texture_as__allocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    set_texture_flags_as__allocated(
            PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
                p_PLATFORM_texture));
}

static inline
void SDL_set_texture_as__deallocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    set_texture_flags_as__deallocated(
            PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
                p_PLATFORM_texture));
}

#endif
