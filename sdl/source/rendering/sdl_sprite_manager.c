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

PLATFORM_Sprite *PLATFORM_allocate_sprite__TMP(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        PLATFORM_Texture *p_PLATFORM_texture_to__sample_by__sprite,
        Texture_Flags texture_flags_for__sprite) {
    SDL_Sprite_Manager *p_SDL_sprite_manager =
        SDL_get_p_sprite_manager_from__gfx_context(
                p_PLATFORM_gfx_context);

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
        / get_texture_flags__width(texture_flags_for__sprite);
    p_PLATFORM_sprite->quantity_of__sprite_frame__rows =
        p_PLATFORM_texture_to__sample_by__sprite
        ->height
        / get_texture_flags__height(texture_flags_for__sprite);
    p_PLATFORM_sprite->sprite_frame__width = 
        1.0 
        / (float)p_PLATFORM_sprite->quantity_of__sprite_frame__columns;
    p_PLATFORM_sprite->sprite_frame__height = 
        1.0 
        / (float)p_PLATFORM_sprite->quantity_of__sprite_frame__rows;
    
    return p_PLATFORM_sprite;
}

PLATFORM_Sprite *PLATFORM_allocate_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context, 
        Sprite_Allocation_Specification *p_sprite_allocation_specification) {

    SDL_Texture_Manager *p_SDL_texture_manager = 
        SDL_get_p_texture_manager_from__gfx_context(
                p_PLATFORM_gfx_context);

    PLATFORM_Texture *p_PLATFORM_texture = 0;
    bool is_texture__anonymous = false;

    switch (p_sprite_allocation_specification
            ->the_kind_of__sprite_allocation) {
        case Sprite_Allocation_Kind__None:
            debug_abort("SDL::PLATFORM_allocate_sprite, Sprite_Allocation_Kind__None.");
            break;
        default:
        case Sprite_Allocation_Kind__Graphics_Pointer:
            p_PLATFORM_texture = 
                SDL_allocate_texture_with__texture_manager(
                        p_SDL_texture_manager);
            if (!p_PLATFORM_texture) {
                debug_error("SDL::PLATFORM_allocate_sprite, failed to allocate anonymous texture.");
                return 0;
            }
            p_PLATFORM_texture =
                PLATFORM_allocate_texture(
                        p_PLATFORM_gfx_context, 
                        &p_sprite_allocation_specification
                        ->texture_allocation_specification);
            debug_error("SDL::PLATFORM_allocate_sprite impl");
            // TODO: verify that the allocation suceeded.
            is_texture__anonymous = true;
            break;
        case Sprite_Allocation_Kind__Entity:
        case Sprite_Allocation_Kind__Item:
        case Sprite_Allocation_Kind__Particle:
        case Sprite_Allocation_Kind__UI:
            ;
            SDL_Texture_String__Const *p_ptr_SDL_texture_string = 
                SDL_get_texture_string_from__sprite_allocation_specification(
                        p_sprite_allocation_specification);

            if (!p_ptr_SDL_texture_string) {
                debug_error("SDL::PLATFORM_allocate_sprite, unsupported type.");
                return 0;
            }

            p_PLATFORM_texture =
                SDL_get_texture_from__texture_manager(
                        p_SDL_texture_manager, 
                        *p_ptr_SDL_texture_string);

            if (!p_PLATFORM_texture) {
                debug_error("SDL::PLATFORM_allocate_sprite, texture is not loaded for: %s",
                        p_ptr_SDL_texture_string);
                return 0;
            }

            break;
    }

    SDL_Sprite_Manager *p_SDL_sprite_manager =
        SDL_get_p_sprite_manager_from__gfx_context(
                p_PLATFORM_gfx_context);

    PLATFORM_Sprite *p_PLATFORM_sprite =
        SDL_allocate_sprite_with__sprite_manager(
                p_SDL_sprite_manager);

    if (!p_PLATFORM_sprite) {
        debug_error("SDL::PLATFORM_allocate_sprite, failed to allocate sprite.");
        if (is_texture__anonymous) {
            PLATFORM_release_texture(
                    p_PLATFORM_gfx_context,
                    p_PLATFORM_texture);
        }
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
        if (is_texture__anonymous) {
            PLATFORM_release_texture(
                    p_PLATFORM_gfx_context,
                    p_PLATFORM_texture);
        }
        return 0;
    }

    p_PLATFORM_sprite->p_PLATFORM_texture =
        p_PLATFORM_texture;
    p_PLATFORM_sprite->is_sprite_with__anonymous_texture =
        is_texture__anonymous;

    SDL_initialize_sprite(
            p_PLATFORM_gfx_context,
            p_PLATFORM_sprite);

    // TODO: load sprite data from yml
    p_PLATFORM_sprite->quantity_of__sprite_frame__columns = 16;
    p_PLATFORM_sprite->quantity_of__sprite_frame__rows = 16;
    p_PLATFORM_sprite->sprite_frame__width = 1.0 / 16.0;
    p_PLATFORM_sprite->sprite_frame__height = 1.0 / 16.0;
    switch (p_sprite_allocation_specification
            ->the_kind_of__sprite_allocation) {
        default:
            break;
        case Sprite_Allocation_Kind__Item:
            p_PLATFORM_sprite->quantity_of__sprite_frame__columns = 32;
            p_PLATFORM_sprite->quantity_of__sprite_frame__rows = 32;
            p_PLATFORM_sprite->sprite_frame__width = 1.0 / 32.0;
            p_PLATFORM_sprite->sprite_frame__height = 1.0 / 32.0;
            break;
        case Sprite_Allocation_Kind__UI:
            if (p_sprite_allocation_specification
                    ->the_kind_of__ui__this_sprite_is
                    < UI_Sprite_Kind__8x8) {
                p_PLATFORM_sprite->quantity_of__sprite_frame__columns = 32;
                p_PLATFORM_sprite->quantity_of__sprite_frame__rows = 32;
                p_PLATFORM_sprite->sprite_frame__width = 1.0 / 32.0;
                p_PLATFORM_sprite->sprite_frame__height = 1.0 / 32.0;
            } else if (p_sprite_allocation_specification
                    ->the_kind_of__ui__this_sprite_is
                    >= UI_Sprite_Kind__16x16) {
                p_PLATFORM_sprite->quantity_of__sprite_frame__columns = 8;
                p_PLATFORM_sprite->quantity_of__sprite_frame__rows = 8;
                p_PLATFORM_sprite->sprite_frame__width = 1.0 / 8.0;
                p_PLATFORM_sprite->sprite_frame__height = 1.0 / 8.0;
            }
            break;
    }

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
