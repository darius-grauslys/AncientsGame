#include <rendering/sdl_sprite.h>

void SDL_initialize_sprite_as__deallocated(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    SDL_set_sprite_as__deallocated(
            p_PLATFORM_sprite);

    p_PLATFORM_sprite->p_PLATFORM_texture = 0;
    p_PLATFORM_sprite->p_SDL_sprite = 0;
    p_PLATFORM_sprite->quantity_of__sprite_frame__columns =
        p_PLATFORM_sprite->quantity_of__sprite_frame__rows = 0;
}
