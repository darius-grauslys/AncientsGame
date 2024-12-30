#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_texture.h"
#include "rendering/texture.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL2/SDL_pixels.h>
#include <rendering/opengl/gl_texture.h>
#include <sdl_defines.h>
#include <stdio.h>
#include "rendering/sdl_texture_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <rendering/stb_image.h>

void GL_initialize_texture_as__deallocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    p_PLATFORM_texture
        ->GL_texture_handle = 0;
    SDL_initialize_texture_as__deallocated(
            p_PLATFORM_texture);
}

int GL_get_texture_format(
        PLATFORM_Texture *p_PLATFORM_texture) {
    switch (p_PLATFORM_texture->SDL_texture_format__u32) {
        default:
        case SDL_PIXELFORMAT_RGBA5551:
            return GL_RGBA;
        case SDL_PIXELFORMAT_RGB888:
            return GL_RGB;
        case SDL_PIXELFORMAT_RGBA8888:
            return GL_RGBA;
    }

}

PLATFORM_Texture *GL_allocate_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {
    PLATFORM_Texture *p_PLATFORM_texture =
        SDL_allocate_texture_with__texture_manager(
                SDL_get_p_texture_manager_from__gfx_context(
                    p_PLATFORM_gfx_context));
    if (!p_PLATFORM_texture)
        return p_PLATFORM_texture;
    glGenTextures(
            1,
            GL_get_p_texture_handle(
                p_PLATFORM_texture)
            );
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        set_texture_flags_as__deallocated(
                &p_PLATFORM_texture
                ->texture_flags);
        debug_error("SDL::GL::PLATFORM_allocate_texture failed. (glGenTextures)");
        return 0;
    }

    glBindTexture(
            GL_TEXTURE_2D,
            GL_get_texture_handle(p_PLATFORM_texture));

    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_WRAP_S, 
            GL_CLAMP);
    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_WRAP_T, 
            GL_CLAMP);

    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MIN_FILTER, 
            GL_NEAREST);
    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MAG_FILTER, 
            GL_NEAREST);

    SDL_update_texture_format_and__access(
            p_PLATFORM_texture, 
            p_texture_allocation_specification
            ->texture_flags);

    u32 GL_format =
        GL_get_texture_format(
                p_PLATFORM_texture);

    glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            p_PLATFORM_texture->width, 
            p_PLATFORM_texture->height, 
            0, 
            GL_format, 
            GL_UNSIGNED_BYTE, 
            0);

    // TODO: this leaks atm, check glGetError on each step, and clean up as needed.
    error = glGetError();
    if (error != GL_NO_ERROR) {
        set_texture_flags_as__deallocated(
                &p_PLATFORM_texture
                ->texture_flags);
        debug_error("SDL::GL::PLATFORM_allocate_texture failed. (glTexImage2D:%x)", error);
        return 0;
    }

    set_texture_flags_as__allocated(
            &p_PLATFORM_texture
            ->texture_flags);

    return p_PLATFORM_texture;
}

PLATFORM_Texture *GL_allocate_texture__with_path(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification 
            *p_texture_allocation_specification,
        const char *path) {
    PLATFORM_Texture *p_PLATFORM_texture = 
        GL_allocate_texture(
                p_PLATFORM_gfx_context, 
                p_texture_allocation_specification);

    if (!p_PLATFORM_texture)
        return 0;

    int width, height, channels, requested_channels;

    switch (p_PLATFORM_texture->SDL_texture_format__u32) {
        default:
        case SDL_PIXELFORMAT_RGBA5551:
            requested_channels = 2;
            break;
        case SDL_PIXELFORMAT_RGB888:
            requested_channels = 3;
            break;
        case SDL_PIXELFORMAT_RGBA8888:
            requested_channels = 4;
            break;
    }

    stbi_set_flip_vertically_on_load(true);

    u8 *p_data = 
        stbi_load(
                path,
                &width,
                &height,
                &channels,
                requested_channels
                );

    if (!p_data) {
        PLATFORM_release_texture(
                &__SDL_Gfx_Context,
                p_PLATFORM_texture);
        debug_error("SDL::GL::PLATFORM_allocate_texture__with_path failed. (stbi_load)");
        return 0;
    }

    if (width != p_PLATFORM_texture->width) {
        debug_warning("SDL::GL::PLATFORM_allocate_texture__with_path, invalid width.");
    }

    if (height != p_PLATFORM_texture->height) {
        debug_warning("SDL::GL::PLATFORM_allocate_texture__with_path, invalid height.");
    }

    if (channels != requested_channels) {
        debug_warning("SDL::GL::PLATFORM_allocate_texture__with_path, invalid channels.");
    }

    u32 GL_format =
        GL_get_texture_format(
                p_PLATFORM_texture);

    glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            width, 
            height, 
            0, 
            GL_format, 
            GL_UNSIGNED_BYTE, 
            p_data);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        PLATFORM_release_texture(
                &__SDL_Gfx_Context,
                p_PLATFORM_texture);
        debug_error("SDL::GL::PLATFORM_allocate_texture__with_path failed. (glTexImage2D:%d)", error);
        return 0;
    }

    set_texture_flags_as__allocated(
            &p_PLATFORM_texture
            ->texture_flags);

    stbi_image_free(p_data);

    return p_PLATFORM_texture;
}

PLATFORM_Texture *GL_allocate_texture__TMP(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags) {
    PLATFORM_Texture *p_PLATFORM_texture =
        SDL_allocate_texture_with__texture_manager(
                SDL_get_p_texture_manager_from__gfx_context(
                    p_PLATFORM_gfx_context));
    if (!p_PLATFORM_texture)
        return p_PLATFORM_texture;
    glGenTextures(
            1,
            GL_get_p_texture_handle(
                p_PLATFORM_texture)
            );
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        set_texture_flags_as__deallocated(
                &p_PLATFORM_texture
                ->texture_flags);
        debug_error("SDL::GL::PLATFORM_allocate_texture failed. (glGenTextures)");
        return 0;
    }

    glBindTexture(
            GL_TEXTURE_2D,
            GL_get_texture_handle(p_PLATFORM_texture));

    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_WRAP_S, 
            GL_CLAMP);
    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_WRAP_T, 
            GL_CLAMP);

    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MIN_FILTER, 
            GL_NEAREST);
    glTexParameteri(
            GL_TEXTURE_2D, 
            GL_TEXTURE_MAG_FILTER, 
            GL_NEAREST);

    SDL_update_texture_format_and__access(
            p_PLATFORM_texture, 
            texture_flags);

    u32 GL_format =
        GL_get_texture_format(
                p_PLATFORM_texture);

    glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            p_PLATFORM_texture->width, 
            p_PLATFORM_texture->height, 
            0, 
            GL_format, 
            GL_UNSIGNED_BYTE, 
            0);

    // TODO: this leaks atm, check glGetError on each step, and clean up as needed.
    error = glGetError();
    if (error != GL_NO_ERROR) {
        set_texture_flags_as__deallocated(
                &p_PLATFORM_texture
                ->texture_flags);
        debug_error("SDL::GL::PLATFORM_allocate_texture failed. (glTexImage2D:%x)", error);
        return 0;
    }

    set_texture_flags_as__allocated(
            &p_PLATFORM_texture
            ->texture_flags);

    return p_PLATFORM_texture;
}

PLATFORM_Texture *GL_allocate_texture__with_path__TMP(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Flags texture_flags,
        const char *path) {
    PLATFORM_Texture *p_PLATFORM_texture = 
        GL_allocate_texture__TMP(
                p_PLATFORM_gfx_context, 
                texture_flags);

    if (!p_PLATFORM_texture)
        return 0;

    int width, height, channels, requested_channels;

    switch (p_PLATFORM_texture->SDL_texture_format__u32) {
        default:
        case SDL_PIXELFORMAT_RGBA5551:
            requested_channels = 2;
            break;
        case SDL_PIXELFORMAT_RGB888:
            requested_channels = 3;
            break;
        case SDL_PIXELFORMAT_RGBA8888:
            requested_channels = 4;
            break;
    }

    stbi_set_flip_vertically_on_load(true);

    u8 *p_data = 
        stbi_load(
                path,
                &width,
                &height,
                &channels,
                requested_channels
                );

    if (!p_data) {
        PLATFORM_release_texture(
                &__SDL_Gfx_Context,
                p_PLATFORM_texture);
        debug_error("SDL::GL::PLATFORM_allocate_texture__with_path failed. (stbi_load)");
        return 0;
    }

    if (width != p_PLATFORM_texture->width) {
        debug_warning("SDL::GL::PLATFORM_allocate_texture__with_path, invalid width.");
    }

    if (height != p_PLATFORM_texture->height) {
        debug_warning("SDL::GL::PLATFORM_allocate_texture__with_path, invalid height.");
    }

    if (channels != requested_channels) {
        debug_warning("SDL::GL::PLATFORM_allocate_texture__with_path, invalid channels.");
    }

    u32 GL_format =
        GL_get_texture_format(
                p_PLATFORM_texture);

    glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            width, 
            height, 
            0, 
            GL_format, 
            GL_UNSIGNED_BYTE, 
            p_data);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        PLATFORM_release_texture(
                &__SDL_Gfx_Context,
                p_PLATFORM_texture);
        debug_error("SDL::GL::PLATFORM_allocate_texture__with_path failed. (glTexImage2D:%d)", error);
        return 0;
    }

    set_texture_flags_as__allocated(
            &p_PLATFORM_texture
            ->texture_flags);

    stbi_image_free(p_data);

    return p_PLATFORM_texture;
}

void GL_use_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    glBindTexture(
            GL_TEXTURE_2D,
            p_PLATFORM_texture->GL_texture_handle);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        debug_error("SDL::GL::PLATFORM_use_texture failed. (glBindTexture)");
        return;
    }
}

void GL_release_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    glDeleteTextures(
            1,
            &p_PLATFORM_texture->GL_texture_handle);

    set_texture_flags_as__deallocated(
            &p_PLATFORM_texture
            ->texture_flags);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        debug_error("SDL::GL::PLATFORM_release_texture failed. (glDeleteTextures)");
        return;
    }
}
