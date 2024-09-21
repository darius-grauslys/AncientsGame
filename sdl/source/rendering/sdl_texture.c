#include "defines.h"
#include "rendering/texture.h"
#include "sdl_defines.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <rendering/sdl_texture.h>

void SDL_update_texture_format_and__access(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {
    SDL_Texture_Format__u32 SDL_texture_format;
    switch (get_texture_flags__format(
                p_texture_allocation_specification
                ->texture_flags)) {
        default:
        case TEXTURE_FLAG__FORMAT__15_RGB:
            SDL_texture_format = 
                SDL_PIXELFORMAT_RGBA5551;
            break;
        case TEXTURE_FLAG__FORMAT__RGB888:
            SDL_texture_format = 
                SDL_PIXELFORMAT_RGB888;
            break;
        case TEXTURE_FLAG__FORMAT__RGBA8888:
            SDL_texture_format = 
                SDL_PIXELFORMAT_RGBA8888;
            break;
    }

    SDL_TextureAccess SDL_texture_access;
    switch (get_texture_flags__rendering_method(
                p_texture_allocation_specification
                ->texture_flags)) {
        default:
        case TEXTURE_FLAG__RENDER_METHOD__0:
            SDL_texture_access =
                SDL_TEXTUREACCESS_STATIC;
            break;
        case TEXTURE_FLAG__RENDER_METHOD__1:
            SDL_texture_access =
                SDL_TEXTUREACCESS_STREAMING;
            break;
        case TEXTURE_FLAG__RENDER_METHOD__2:
            SDL_texture_access =
                SDL_TEXTUREACCESS_TARGET;
            break;
    }

    p_PLATFORM_texture->width =
        get_length_of__texture_flag__width(
                p_texture_allocation_specification
                ->texture_flags);
    p_PLATFORM_texture->height =
        get_length_of__texture_flag__height(
                p_texture_allocation_specification
                ->texture_flags);

    p_PLATFORM_texture->SDL_texture_access =
        SDL_texture_access;
    p_PLATFORM_texture->SDL_texture_format__u32 =
        SDL_texture_format;
}
