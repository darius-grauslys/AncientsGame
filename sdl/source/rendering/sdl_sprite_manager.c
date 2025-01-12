#include "debug/debug.h"
#include "defines_weak.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_sprite.h"
#include "rendering/sdl_texture_manager.h"
#include "rendering/sdl_texture_strings.h"
#include "rendering/texture.h"
#include "sdl_defines.h"
#include <rendering/sdl_sprite_manager.h>
#include "rendering/gfx_context.h"
#include <defines.h>

void SDL_initialize_sprite_manager(
        SDL_Sprite_Manager *p_SDL_sprite_manager) {
    for (Index__u16 index_of__sdl_sprite = 0;
            index_of__sdl_sprite < MAX_QUANTITY_OF__SPRITES;
            index_of__sdl_sprite++) {
        PLATFORM_Sprite *p_PLATFORM_sprite =
            &p_SDL_sprite_manager
            ->SDL_sprites[index_of__sdl_sprite];
        SDL_initialize_sprite_as__deallocated(
                p_PLATFORM_sprite);
    }
}

PLATFORM_Sprite *SDL_allocate_sprite_with__sprite_manager(
        SDL_Sprite_Manager *p_SDL_sprite_manager) {
    for (Index__u16 index_of__sdl_sprite = 0;
            index_of__sdl_sprite < MAX_QUANTITY_OF__SPRITES;
            index_of__sdl_sprite++) {
        PLATFORM_Sprite *p_PLATFORM_sprite =
            &p_SDL_sprite_manager
            ->SDL_sprites[index_of__sdl_sprite];
        if (SDL_is_sprite__allocated(
                    p_PLATFORM_sprite)) {
            continue;
        }

        SDL_set_sprite_as__allocated(
                p_PLATFORM_sprite);
        return p_PLATFORM_sprite;
    }

    return 0;
}

void SDL_release_sprite_from__sprite_manager(
        SDL_Sprite_Manager *p_SDL_sprite_manager,
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    u16 index =
        p_PLATFORM_sprite
        - p_SDL_sprite_manager
        ->SDL_sprites
        ;
    
    if (index < 0 || index >= MAX_QUANTITY_OF__SPRITES) {
        debug_abort("SDL::SDL_release_sprite_from__sprite_manager, p_PLATFORM_sprite is not allocated with this manager, or is invalid.");
        debug_warning("This might cause a GPU memory leak!");
        return;
    }

    SDL_set_sprite_as__deallocated(
            p_PLATFORM_sprite);
}

void SDL_dispose_sprite_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        SDL_Sprite_Manager *p_SDL_sprite_manager) {
    for (Index__u16 index_of__sdl_sprite = 0;
            index_of__sdl_sprite < MAX_QUANTITY_OF__SPRITES;
            index_of__sdl_sprite++) {
        PLATFORM_Sprite *p_PLATFORM_sprite =
            &p_SDL_sprite_manager
            ->SDL_sprites[index_of__sdl_sprite];
        if (!SDL_is_sprite__allocated(
                    p_PLATFORM_sprite)) {
            continue;
        }

        PLATFORM_release_sprite(
                p_PLATFORM_gfx_context,
                p_PLATFORM_sprite);
    }
}

PLATFORM_Sprite *PLATFORM_allocate_sprite(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        PLATFORM_Texture *p_PLATFORM_texture_to__sample_by__sprite,
        Texture_Flags texture_flags_for__sprite) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__gfx_context(p_gfx_context);

    SDL_Sprite_Manager *p_SDL_sprite_manager =
        SDL_get_p_sprite_manager_from__gfx_context(p_PLATFORM_gfx_context);

    PLATFORM_Sprite *p_PLATFORM_sprite =
        SDL_allocate_sprite_with__sprite_manager(
                p_SDL_sprite_manager);

    if (!p_PLATFORM_sprite) {
        debug_error("SDL::PLATFORM_allocate_sprite, failed to allocate sprite.");
        return 0;
    }

    p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_sprite(
                p_PLATFORM_gfx_context,
                p_PLATFORM_sprite);

    if (!p_PLATFORM_sprite->p_SDL_sprite) {
        SDL_release_sprite_from__sprite_manager(
                p_SDL_sprite_manager,
                p_PLATFORM_sprite);
        return 0;
    }

    p_PLATFORM_sprite->p_PLATFORM_texture =
        p_PLATFORM_texture_to__sample_by__sprite;
    p_PLATFORM_sprite->is_sprite_with__anonymous_texture = false;

    SDL_initialize_sprite(
            p_PLATFORM_gfx_context,
            p_PLATFORM_sprite);

    p_PLATFORM_sprite->quantity_of__sprite_frame__columns = 
        p_PLATFORM_texture_to__sample_by__sprite
        ->width
        / get_length_of__texture_flag__width(texture_flags_for__sprite);
    p_PLATFORM_sprite->quantity_of__sprite_frame__rows =
        p_PLATFORM_texture_to__sample_by__sprite
        ->height
        / get_length_of__texture_flag__height(texture_flags_for__sprite);
    p_PLATFORM_sprite->sprite_frame__width = 
        1.0 
        / (float)p_PLATFORM_sprite->quantity_of__sprite_frame__columns;
    p_PLATFORM_sprite->sprite_frame__height = 
        1.0 
        / (float)p_PLATFORM_sprite->quantity_of__sprite_frame__rows;
    
    return p_PLATFORM_sprite;
}

void PLATFORM_release_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context, 
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    if (p_PLATFORM_sprite->is_sprite_with__anonymous_texture) {
        PLATFORM_release_texture(
                p_PLATFORM_gfx_context,
                p_PLATFORM_sprite
                ->p_PLATFORM_texture);
    }
    p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_release_sprite(
                p_PLATFORM_gfx_context,
                p_PLATFORM_sprite);
    SDL_release_sprite_from__sprite_manager(
            SDL_get_p_sprite_manager_from__gfx_context(
                p_PLATFORM_gfx_context), 
            p_PLATFORM_sprite);

    SDL_initialize_sprite_as__deallocated(
            p_PLATFORM_sprite);
}
