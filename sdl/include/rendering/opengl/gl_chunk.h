#ifndef GL_CHUNK_H
#define GL_CHUNK_H

#include "gl_defines.h"

void GL_render_chunk(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

void GL_update_chunk(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

void GL_update_chunks(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager);

#endif
