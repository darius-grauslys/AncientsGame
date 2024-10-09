#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "platform_defines.h"
#include <rendering/opengl/gl_chunk_texture.h>
#include <rendering/opengl/gl_texture.h>

void GL_initialize_chunk_texture_as__deallocated(
        GL_Chunk_Texture *p_GL_chunk_texture) {
    GL_initialize_texture_as__deallocated(
            &p_GL_chunk_texture->GL_chunk_texture);
    p_GL_chunk_texture->p_chunk_owner = 0;
}

void GL_allocate_chunk_texture__texture_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture *p_GL_chunk_texture) {
    Texture_Allocation_Specification texture_alloc_spec;

    texture_alloc_spec.texture_flags =
        TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_64x64, 
                TEXTURE_FLAG__RENDER_METHOD__0, 
                TEXTURE_FLAG__FORMAT__RGBA8888);

    PLATFORM_allocate_texture(
            &p_GL_chunk_texture
            ->GL_chunk_texture, 
            &texture_alloc_spec);
    PLATFORM_allocate_texture(
            &p_GL_chunk_texture
            ->GL_chunk_texture__sprite_cover, 
            &texture_alloc_spec);
}

void GL_deallocate_chunk_texture__texture_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture *p_GL_chunk_texture) {
    PLATFORM_release_texture(
            p_PLATFORM_gfx_context, 
            &p_GL_chunk_texture->GL_chunk_texture);
}

