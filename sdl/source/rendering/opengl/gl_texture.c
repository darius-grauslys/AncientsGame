#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "rendering/sdl_texture.h"
#include "rendering/texture.h"
#include <GL/gl.h>
#include <SDL2/SDL_pixels.h>
#include <rendering/opengl/gl_texture.h>
#include <sdl_defines.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <rendering/stb_image.h>

static inline
GLint GL_get_texture_format(
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

void GL_allocate_texture(
        PLATFORM_Texture *p_PLATFORM_texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification) {
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
        return;
    }

    glBindTexture(
            GL_TEXTURE_2D,
            GL_get_texture_handle(p_PLATFORM_texture));

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
            p_texture_allocation_specification);

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

    error = glGetError();
    if (error != GL_NO_ERROR) {
        set_texture_flags_as__deallocated(
                &p_PLATFORM_texture
                ->texture_flags);
        debug_error("SDL::GL::PLATFORM_allocate_texture failed. (glTexImage2D:%x)", error);
        return;
    }

    set_texture_flags_as__allocated(
            &p_PLATFORM_texture
            ->texture_flags);
}

void GL_allocate_texture__with_path(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Allocation_Specification 
            *p_texture_allocation_specification,
        const char *path) {
    GL_allocate_texture(
            p_PLATFORM_texture, 
            p_texture_allocation_specification);

    if (!is_texture_flags__allocated(
                p_PLATFORM_texture
                ->texture_flags)) {
        return;
    }

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
        PLATFORM_release_texture(p_PLATFORM_texture);
        debug_error("SDL::GL::PLATFORM_allocate_texture__with_path failed. (stbi_load)");
        return;
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
        set_texture_flags_as__deallocated(
                &p_PLATFORM_texture
                ->texture_flags);
        debug_error("SDL::GL::PLATFORM_allocate_texture__with_path failed. (glTexImage2D:%d)", error);
        return;
    }

    set_texture_flags_as__allocated(
            &p_PLATFORM_texture
            ->texture_flags);

    stbi_image_free(p_data);
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
