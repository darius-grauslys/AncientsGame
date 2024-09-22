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

// TODO: auto-gen this file.

static inline
bool _SDL_load_texture(
        SDL_Texture_Manager *p_SDL_texture_manager,
        Asset_Directory_Kind the_kind_of__asset_directory,
        const char *p_path,
        SDL_Texture_String__Const p_SDL_texture_name,
        Texture_Flags size_of__texture,
        Texture_Flags render_method_of__texture,
        Texture_Flags format_of__texture,
        Texture_Allocation_Specification *p_texture_allocation_specification,
        bool *p_result__current) {
    *p_result__current = 
        SDL_get_path_to__texture_file(
                Asset_Directory_Kind__Entity_Sprite__16x16, 
                (char*)p_path, 
                SDL_texture_string__player);
    if (*p_result__current) {
        PLATFORM_Texture *p_PLATFORM_texture =
            SDL_allocate_texture_with__texture_manager(
                    p_SDL_texture_manager);
        if (p_PLATFORM_texture) {
            p_texture_allocation_specification
                ->texture_flags = TEXTURE_FLAGS(
                        TEXTURE_FLAG__SIZE_16x16, 
                        TEXTURE_FLAG__RENDER_METHOD__0, 
                        TEXTURE_FLAG__FORMAT__RGBA8888);
            memcpy(
                    p_PLATFORM_texture->SDL_texture_string,
                    p_SDL_texture_name,
                    MAX_LENGTH_OF__SDL_TEXTURE_STRING);
            PLATFORM_allocate_texture__with_path(
                    p_PLATFORM_texture, 
                    p_texture_allocation_specification, 
                    p_path);
        } else {
            return false;
        }
    }
    return true;
}

bool SDL_load_textures(Game *p_game) {
    SDL_Texture_Manager *p_SDL_texture_manager =
        SDL_get_p_texture_manager_from__gfx_context(
                get_p_PLATFORM_gfx_context_from__game(p_game));

    bool result = true;
    bool result__current = false;

    char path[1024];

    Texture_Allocation_Specification texture_allocation_specification;
    texture_allocation_specification.p_PLATFORM_graphics_window = 0;

    if (!_SDL_load_texture(
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

    return result;
failure_to__allocate:
    debug_abort("SDL::SDL_load_textures, failed to allocate p_PLATFORM_texture.");
    return false;
}
