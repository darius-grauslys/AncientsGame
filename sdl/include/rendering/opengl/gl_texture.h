#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "defines_weak.h"
#include "rendering/opengl/gl_platform_defines.h"
#include <defines.h>
#include <sdl_defines.h>

void GL_initialize_texture_as__deallocated(
        PLATFORM_Texture *p_PLATFORM_texture);

PLATFORM_Texture *GL_allocate_texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

PLATFORM_Texture *GL_allocate_texture__with_path(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Texture_Allocation_Specification 
            *p_texture_allocation_specification,
        const char *path);

void GL_use_texture(PLATFORM_Texture *texture);

void GL_release_texture(PLATFORM_Texture *texture);

int GL_get_texture_format(
        PLATFORM_Texture *p_PLATFORM_texture);

static inline
GL_Texture_Handle__u32 GL_get_texture_handle(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return p_PLATFORM_texture->GL_texture_handle;
}

static inline
GL_Texture_Handle__u32 *GL_get_p_texture_handle(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return &p_PLATFORM_texture->GL_texture_handle;
}

#endif
