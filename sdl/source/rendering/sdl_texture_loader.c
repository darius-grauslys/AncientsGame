#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_texture_manager.h"
#include "rendering/sdl_texture_strings.h"
#include "sdl_defines.h"
#include "serialization/sdl_filesystem.h"
#include "serialization/sdl_filesystem_defines.h"
#include <rendering/sdl_texture_loader.h>

static inline
bool _SDL_load_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        SDL_Texture_Manager *p_SDL_texture_manager,
        Asset_Directory_Kind the_kind_of__asset_directory,
        const char *p_path,
        SDL_Texture_String__Const p_SDL_texture_name,
        Texture_Flags size_of__texture,
        Texture_Flags render_method_of__texture,
        Texture_Flags format_of__texture,
        Texture_Allocation_Specification *p_texture_allocation_specification,
        bool *p_result__current) {
    debug_info("_SDL_load_texture: %s", p_SDL_texture_name);
    *p_result__current = 
        SDL_get_path_to__texture_file(
                the_kind_of__asset_directory, 
                (char*)p_path, 
                p_SDL_texture_name);
    if (*p_result__current) {
        p_texture_allocation_specification
            ->texture_flags = TEXTURE_FLAGS(
                    size_of__texture, 
                    render_method_of__texture, 
                    format_of__texture);
        PLATFORM_Texture *p_PLATFORM_texture =
            PLATFORM_allocate_texture__with_path(
                    p_PLATFORM_gfx_context, 
                    p_texture_allocation_specification, 
                    p_path);
        if (!p_PLATFORM_texture)
            return false;
        memcpy(
                p_PLATFORM_texture->SDL_texture_string,
                p_SDL_texture_name,
                MAX_LENGTH_OF__SDL_TEXTURE_STRING);
        return true;
    }
    debug_error("_SDL_load_texture failed to find path: %s", p_path);
    return false;
}

// TODO: auto-gen this part of the file.

bool SDL_load_textures(Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);
    SDL_Texture_Manager *p_SDL_texture_manager =
        SDL_get_p_texture_manager_from__gfx_context(
                p_PLATFORM_gfx_context);

    bool result = true;
    bool result__current = false;

    char path[1024];

    Texture_Allocation_Specification texture_allocation_specification;
    texture_allocation_specification.p_PLATFORM_graphics_window = 0;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__Entity_Sprite__16x16, 
                path, 
                SDL_texture_string__player, 
                TEXTURE_FLAG__SIZE_16x16, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__Entity_Sprite__16x16, 
                path, 
                SDL_texture_string__skeleton, 
                TEXTURE_FLAG__SIZE_16x16, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__World, 
                path, 
                SDL_texture_string__tilesheet_cover, 
                TEXTURE_FLAG__SIZE_256x256, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__World, 
                path, 
                SDL_texture_string__tilesheet_ground, 
                TEXTURE_FLAG__SIZE_256x256, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__UI__Default, 
                path, 
                SDL_texture_string__tilesheet_ui, 
                TEXTURE_FLAG__SIZE_256x256, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__Entity_Sprite__8x8, 
                path, 
                SDL_texture_string__items, 
                TEXTURE_FLAG__SIZE_256x256, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__UI__Sprite__8x8, 
                path, 
                SDL_texture_string__ui_sprites__8x8, 
                TEXTURE_FLAG__SIZE_256x256, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__UI__Sprite__16x16, 
                path, 
                SDL_texture_string__ui_sprites__16x16, 
                TEXTURE_FLAG__SIZE_256x256, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    if (!_SDL_load_texture(
                p_PLATFORM_gfx_context,
                p_SDL_texture_manager,
                Asset_Directory_Kind__UI__Sprite__32x32, 
                path, 
                SDL_texture_string__ui_sprites__32x32, 
                TEXTURE_FLAG__SIZE_256x256, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888, 
                &texture_allocation_specification, 
                &result__current)) {
        goto failure_to__allocate;
    }
    result &= result__current;

    return result;
failure_to__allocate:
    debug_abort("SDL::SDL_load_textures, failed to allocate p_PLATFORM_texture.");
    return false;
}
