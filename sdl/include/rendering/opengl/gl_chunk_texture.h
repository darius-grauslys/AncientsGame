#ifndef GL_CHUNK_TEXTURE_H
#define GL_CHUNK_TEXTURE_H

#include "defines_weak.h"
#include "gl_defines.h"
#include "rendering/sdl_texture.h"

void GL_initialize_chunk_texture_as__deallocated(
        GL_Chunk_Texture *p_GL_chunk_texture);

void GL_allocate_chunk_texture__texture_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture *p_GL_chunk_texture);

void GL_deallocate_chunk_texture__texture_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture *p_GL_chunk_texture);

static inline
bool GL_is_chunk_texture__allocated(
        GL_Chunk_Texture *p_GL_chunk_texture) {
    return 
        SDL_is_texture__allocated(
                &p_GL_chunk_texture->GL_chunk_texture);
}

#endif
