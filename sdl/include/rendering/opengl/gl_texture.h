#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "defines_weak.h"
#include <defines.h>
#include <sdl_defines.h>

void PLATFORM_allocate_texture(
        PLATFORM_Texture *texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

void PLATFORM_use_texture(PLATFORM_Texture *texture);

void PLATFORM_release_texture(PLATFORM_Texture *texture);

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
