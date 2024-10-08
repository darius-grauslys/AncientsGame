#ifndef GL_CHUNK_TEXTURE_MANAGER_H
#define GL_CHUNK_TEXTURE_MANAGER_H

#include "defines_weak.h"
#include "rendering/opengl/gl_defines.h"

void GL_initialize_chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager);

void GL_allocate_chunk_texture_with__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk *p_chunk);

void GL_allocate_chunk_textures_for__chunk_manager_with__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk_Manager *p_chunk_manager);

GL_Chunk_Texture *GL_dehash_chunk_to__chunk_texture(
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        const Chunk *p_chunk);

void GL_deallocate_all_chunk_textures_from__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager);

void GL_deallocate_chunk_textures_for__chunk_manager_from__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk_Manager *p_chunk_manager);

void GL_deallocate_chunk_texture_from__chunk_texture_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Chunk_Texture_Manager *p_GL_chunk_texture_manager,
        Chunk *p_chunk);

#endif
