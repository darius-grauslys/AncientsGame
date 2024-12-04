#include "rendering/sdl_render_world.h"
#include "game.h"

void SDL_render_world(Game *p_game) {
    f_SDL_Render_World f_SDL_render_world =
        get_p_PLATFORM_gfx_context_from__game(
                p_game)
        ->SDL_gfx_sub_context__wrapper
        .f_SDL_render_world
        ;

#ifndef NDEBUG
    if (!f_SDL_render_world) {
        debug_warning("Did you forget to initialize a graphics backend?");
        debug_abort("SDL_render_world, f_SDL_render_world == 0.");
        return;
    }
#endif

    f_SDL_render_world(p_game);
}

void f_SDL_render_world__default(Game *p_game) {
    p_game->p_PLATFORM_gfx_context
        ->SDL_graphics_window__main
        .p_active_camera
        ->m_camera_handler(
                p_game->p_PLATFORM_gfx_context
                ->SDL_graphics_window__main
                .p_active_camera,
                p_game);

    Chunk_Manager *p_chunk_manager =
        get_p_chunk_manager_from__game(p_game);

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
            PLATFORM_render_chunk(
                    get_p_PLATFORM_gfx_context_from__game(p_game),
                    p_current_sub__chunk_map_node);

            p_current_sub__chunk_map_node =
                p_current_sub__chunk_map_node->p_east__chunk_map_node;
        }
        p_current__chunk_map_node =
            p_current__chunk_map_node->p_south__chunk_map_node;
    }

    manage_world(p_game);
}
