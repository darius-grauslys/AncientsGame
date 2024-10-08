#include <rendering/sdl_chunk.h>
#include <defines.h>
#include <sdl_defines.h>

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    f_SDL_Render_Chunk f_SDL_render_chunk =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_render_chunk;

    SDL_ASSERT_HOOK_NULL(
            SDL_render_chunk, 
            p_PLATFORM_gfx_context, 
            f_SDL_render_chunk);

    f_SDL_render_chunk(
            p_PLATFORM_gfx_context,
            p_chunk_map_node);
}

void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Tile *tile) {}

void PLATFORM_update_chunk(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager,
        Chunk_Manager__Chunk_Map_Node *p_chunk_map_node) {
    f_SDL_Update_Chunk f_SDL_update_chunk =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_update_chunk;

    SDL_ASSERT_HOOK_NULL(
            SDL_update_chunk, 
            p_PLATFORM_gfx_context, 
            f_SDL_update_chunk);

    f_SDL_update_chunk(
            p_PLATFORM_gfx_context,
            p_chunk_manager,
            p_chunk_map_node);
}

void PLATFORM_update_chunks(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Chunk_Manager *p_chunk_manager) {
    f_SDL_Update_Chunks f_SDL_update_chunks =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_update_chunks;

    SDL_ASSERT_HOOK_NULL(
            SDL_update_chunks, 
            p_PLATFORM_gfx_context, 
            f_SDL_update_chunks);
    
    f_SDL_update_chunks(
            p_PLATFORM_gfx_context,
            p_chunk_manager);
}
