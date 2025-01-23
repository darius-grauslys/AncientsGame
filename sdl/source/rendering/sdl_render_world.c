#include "rendering/sdl_render_world.h"
#include "rendering/gfx_context.h"
#include "sdl_defines.h"
#include "world/world.h"

void SDL_compose_world(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__gfx_context(p_gfx_context);
    f_SDL_Render_Chunk f_SDL_render_chunk =
        p_PLATFORM_gfx_context
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_render_chunk;
    if (!f_SDL_render_chunk) {
        debug_abort("f_SDL_render_world__default, f_SDL_render_chunk == 0.");
        return;
    }

    Chunk_Manager *p_chunk_manager =
        get_p_chunk_manager_from__world(p_world);

    Chunk_Manager__Chunk_Map_Node *p_current__chunk_map_node =
        p_chunk_manager->p_most_north_western__chunk_map_node;
    Chunk_Manager__Chunk_Map_Node *p_current_sub__chunk_map_node;

    for (uint8_t y=0; 
            y 
            < GFX_CONTEXT__RENDERING_HEIGHT__IN_CHUNKS;
            y++) {
        p_current_sub__chunk_map_node =
            p_current__chunk_map_node;
        for (uint8_t x=0; 
                x 
                < GFX_CONTEXT__RENDERING_WIDTH__IN_CHUNKS;
                x++) {
            f_SDL_render_chunk(
                    p_gfx_context,
                    p_gfx_window,
                    p_current_sub__chunk_map_node);

            p_current_sub__chunk_map_node =
                p_current_sub__chunk_map_node->p_east__chunk_map_node;
        }
        p_current__chunk_map_node =
            p_current__chunk_map_node->p_south__chunk_map_node;
    }
}
