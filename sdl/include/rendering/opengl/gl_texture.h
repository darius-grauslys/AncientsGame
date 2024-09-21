#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "defines_weak.h"
#include <defines.h>
#include <sdl_defines.h>

void GL_allocate_texture(
        PLATFORM_Texture *texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

void GL_allocate_texture__with_path(
        PLATFORM_Texture *p_PLATFORM_texture,
        Texture_Allocation_Specification 
            *p_texture_allocation_specification,
        const char *path);

void GL_use_texture(PLATFORM_Texture *texture);

void GL_release_texture(PLATFORM_Texture *texture);

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
