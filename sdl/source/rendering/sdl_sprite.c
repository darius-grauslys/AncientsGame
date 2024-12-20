#include "debug/debug.h"
#include "sdl_defines.h"
#include <rendering/sdl_sprite.h>

void SDL_initialize_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    f_SDL_Initialize_Sprite f_SDL_initialize_sprite = 
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_initialize_sprite;
#ifndef NDEBUG
    if (!f_SDL_initialize_sprite) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL::SDL_initialize_sprite, f_SDL_initialize_sprite == 0.");
        return;
    }
#endif
    f_SDL_initialize_sprite(
            p_PLATFORM_gfx_context,
            p_PLATFORM_sprite);
}

void SDL_initialize_sprite_as__deallocated(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    SDL_set_sprite_as__deallocated(
            p_PLATFORM_sprite);

    p_PLATFORM_sprite->p_PLATFORM_texture = 0;
    p_PLATFORM_sprite->p_SDL_sprite = 0;
    p_PLATFORM_sprite->quantity_of__sprite_frame__columns =
        p_PLATFORM_sprite->quantity_of__sprite_frame__rows = 0;
}
