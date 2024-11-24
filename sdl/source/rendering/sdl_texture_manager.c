#include "debug/debug.h"
#include "defines_weak.h"
#include "platform_defines.h"
#include "rendering/sdl_gfx_context.h"
#include "sdl_defines.h"
#include <rendering/sdl_texture_manager.h>
#include <rendering/sdl_texture.h>

static inline
PLATFORM_Texture *SDL_get_p_PLATFORM_texture_by__index_from__texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager,
        Index__u32 index_of__sdl_texture) {
#ifndef NDEBUG
    if (index_of__sdl_texture
            >= MAX_QUANTITY_OF__TEXTURES) {
        debug_error("SDL_get_p_PLATFORM_texture_by__index_from__texture_manager, index out of bounds: %d,%d", index_of__sdl_texture, MAX_QUANTITY_OF__TEXTURES);
        return 0;
    }
#endif
    return &p_SDL_texture_manager
        ->SDL_textures[index_of__sdl_texture]
        ;
}

void SDL_initialize_texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager) {
    for (Index__u16 index_of__sdl_texture = 0;
            index_of__sdl_texture < MAX_QUANTITY_OF__TEXTURES;
            index_of__sdl_texture++) {
        PLATFORM_Texture *p_PLATFORM_texture =
            SDL_get_p_PLATFORM_texture_by__index_from__texture_manager(
                    p_SDL_texture_manager,
                    index_of__sdl_texture);
        SDL_initialize_texture_as__deallocated(
                p_PLATFORM_texture);
    }
}

PLATFORM_Texture *SDL_allocate_texture_with__texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager) {
    for (Index__u16 index_of__sdl_texture = 0;
            index_of__sdl_texture < MAX_QUANTITY_OF__TEXTURES;
            index_of__sdl_texture++) {
        PLATFORM_Texture *p_PLATFORM_texture =
            SDL_get_p_PLATFORM_texture_by__index_from__texture_manager(
                    p_SDL_texture_manager, 
                    index_of__sdl_texture);
        if (SDL_is_texture__allocated(
                    p_PLATFORM_texture)) {
            continue;
        }

        SDL_set_texture_as__allocated(p_PLATFORM_texture);
        return p_PLATFORM_texture;
    }

    return 0;
}

PLATFORM_Texture *SDL_get_texture_from__texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager,
        SDL_Texture_String__Const p_SDL_texture_string) {
    for (Index__u16 index_of__sdl_texture = 0;
            index_of__sdl_texture < MAX_QUANTITY_OF__TEXTURES;
            index_of__sdl_texture++) {
        PLATFORM_Texture *p_PLATFORM_texture =
            SDL_get_p_PLATFORM_texture_by__index_from__texture_manager(
                    p_SDL_texture_manager,
                    index_of__sdl_texture);
        if (!SDL_is_texture__allocated(p_PLATFORM_texture)) {
            continue;
        }

        if (strncmp(
                    p_PLATFORM_texture->SDL_texture_string,
                    p_SDL_texture_string,
                    MAX_LENGTH_OF__SDL_TEXTURE_STRING)
                == 0) {
            return p_PLATFORM_texture;
        }
    }

    return 0;
}

void SDL_release_texture_from__texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager,
        PLATFORM_Texture *p_PLATFORM_texture) {
    u16 index =
        p_PLATFORM_texture
        - p_SDL_texture_manager->SDL_textures
        ;

    if (index < 0 || index >= MAX_QUANTITY_OF__TEXTURES) {
        debug_warning("This might cause a GPU memory leak!");
        debug_abort("SDL::SDL_release_texture_from__texture_manager, p_PLATFORM_texture is not allocated with this manager, or is invalid.");
        return;
    }

    SDL_set_texture_as__deallocated(
            p_PLATFORM_texture);
}

void SDL_dispose_texture_manager(
        SDL_Texture_Manager *p_SDL_texture_manager) {
    for (Index__u16 index_of__sdl_texture = 0;
            index_of__sdl_texture < MAX_QUANTITY_OF__TEXTURES;
            index_of__sdl_texture++) {
        PLATFORM_Texture *p_PLATFORM_texture =
            SDL_get_p_PLATFORM_texture_by__index_from__texture_manager(
                    p_SDL_texture_manager,
                    index_of__sdl_texture);
        if (!SDL_is_texture__allocated(p_PLATFORM_texture)) {
            continue;
        }

        PLATFORM_release_texture(
                &__SDL_Gfx_Context,
                p_PLATFORM_texture);
    }
}

PLATFORM_Texture *PLATFORM_allocate_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {
    return __SDL_Gfx_Context
        .SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_texture(
                p_PLATFORM_gfx_context,
                p_texture_allocation_specification);
}

PLATFORM_Texture *PLATFORM_allocate_texture__with_path(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification
            *p_texture_allocation_specification,
        const char *path) {
    return __SDL_Gfx_Context
        .SDL_gfx_sub_context__wrapper
        .f_SDL_allocate_texture__with_path(
                p_PLATFORM_gfx_context,
                p_texture_allocation_specification,
                path);
}

void PLATFORM_use_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Texture *texture) {
    p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_use_texture(
                texture);
}

void PLATFORM_release_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Texture *texture) {
    p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_release_texture(
                texture);
    SDL_release_texture_from__texture_manager(
            SDL_get_p_texture_manager_from__gfx_context(
                p_PLATFORM_gfx_context), 
            texture);
}
