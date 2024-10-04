#ifndef SDL_CHUNK_H
#define SDL_CHUNK_H

#include <defines_weak.h>

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk *chunk);

void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *context,
        Tile *tile);

void PLATFORM_update_chunk(
        PLATFORM_Gfx_Context *p_gfx_context,
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node);

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *gfx_context,
        Chunk_Manager *chunk_manager);

#endif
