#ifndef SDL_SPRITE_H
#define SDL_SPRITE_H

#include <sdl_defines.h>

void SDL_initialize_sprite_as__deallocated(
        PLATFORM_Sprite *p_PLATFORM_sprite);

static inline
bool SDL_is_sprite__allocated(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return p_PLATFORM_sprite->is_sprite__allocated;
}

static inline
void SDL_set_sprite_as__allocated(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    p_PLATFORM_sprite->is_sprite__allocated = true;
}

static inline
void SDL_set_sprite_as__deallocated(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    p_PLATFORM_sprite->is_sprite__allocated = false;
    p_PLATFORM_sprite->is_sprite_with__anonymous_texture = false;
}

#endif
