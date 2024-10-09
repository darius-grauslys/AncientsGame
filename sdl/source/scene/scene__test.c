#include "defines.h"
#include "defines_weak.h"
#include "entity/handlers/entity_handlers.h"
#include "game.h"
#include "input/input.h"
#include "numerics.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "rendering/sdl_chunk.h"
#include "rendering/sdl_gfx_context.h"
#include "sdl_defines.h"
#include "vectors.h"

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context = 
        get_p_PLATFORM_gfx_context_from__game(p_game);

    PLATFORM_initialize_rendering__game(
            p_PLATFORM_gfx_context);
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {

    initialize_world(
            p_game,
            get_p_world_from__game(p_game),
            SDL_get_main_graphics_window_from__gfx_context(
                get_p_PLATFORM_gfx_context_from__game(p_game)));

    Entity *p_player = 
        allocate_entity_into__world(
                p_game,
                get_p_world_from__game(p_game),
                Entity_Kind__Player,
                get_vector__3i32F4_using__i32(0, 0, 0));

    p_game->world.entity_manager
        .p_local_player =
        p_player;

    set_camera_to__track_this__entity(
            &p_game->world.camera, 
            p_player);
    set_camera_to__track_this__entity(
            p_game->p_PLATFORM_gfx_context->p_active_camera,
            p_player);

    move_chunk_manager(
            p_game,
            &p_game->world.chunk_manager, 
            DIRECTION__SOUTH_WEST,
            2);

    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game),
            get_p_chunk_manager_from__game(p_game));

    Chunk_Manager *p_chunk_manager =
        get_p_chunk_manager_from__game(p_game);

    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game__pre_render(p_game);

        p_game->p_PLATFORM_gfx_context->p_active_camera
            ->m_camera_handler(
                    p_game->p_PLATFORM_gfx_context->p_active_camera,
                    p_game);

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
        manage_game__post_render(p_game);
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
