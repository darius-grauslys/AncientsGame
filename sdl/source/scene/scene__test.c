#include "defines.h"
#include "defines_weak.h"
#include "entity/handlers/entity_handlers.h"
#include "entity/humanoid.h"
#include "game.h"
#include "game_action/game_action.h"
#include "input/input.h"
#include "input/sdl_input.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include "platform.h"
#include "platform_defaults.h"
#include "platform_defines.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "rendering/sdl_chunk.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_gfx_window_manager.h"
#include "rendering/sdl_render_world.h"
#include "sdl_defines.h"
#include "sdl_numerics.h"
#include "timer.h"
#include "ui/implemented/ui_registrar__implemented.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include "world/serialization/world_directory.h"
#include "world/world.h"

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context = 
        get_p_PLATFORM_gfx_context_from__game(p_game);

    PLATFORM_initialize_rendering__game(
            p_PLATFORM_gfx_context);

    load_aliased_textures(
            p_game, 
            get_p_aliased_texture_manager_from__game(p_game));
    
    register_ui_windows(
            get_p_gfx_context_from__game(p_game));
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {

    Graphics_Window *p_gfx_window__world =
        allocate_graphics_window_with__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAG__SIZE_256x256);

    set_graphics_window_as__rendering_world(
            p_gfx_window__world);

    initialize_world(
            p_game,
            get_p_world_from__game(p_game),
            SDL_get_main_graphics_window_from__gfx_context(
                get_p_PLATFORM_gfx_context_from__game(p_game)));
    load_world(
            get_p_gfx_context_from__game(p_game),
            get_p_PLATFORM_file_system_context_from__game(p_game),
            get_p_world_from__game(p_game));
    while(!get_p_local_player_from__game(p_game)
            && PLATFORM_get_quantity_of__active_serialization_requests(
                get_p_PLATFORM_file_system_context_from__game(p_game))) {
        manage_game__post_render(p_game); // handle loading first.
    }
    Entity *p_player = 
        p_game->world.entity_manager
            .p_local_player;
    set_camera_to__track_this__entity(
            p_game
            ->gfx_context.p_PLATFORM_gfx_context
            ->SDL_graphics_window__main
            .p_active_camera,
            p_player);
    teleport_player(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            get_p_world_from__game(p_game),
            get_p_local_player_from__game(p_game)
            ->hitbox.position__3i32F4);

    while(PLATFORM_get_quantity_of__active_serialization_requests(
                get_p_PLATFORM_file_system_context_from__game(p_game))) {
        manage_game__post_render(p_game); // handle loading first.
    }

    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game),
            get_p_chunk_manager_from__game(p_game));

    Gfx_Context *p_gfx_context =
        get_p_gfx_context_from__game(p_game);

    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__gfx_context(p_gfx_context);

    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        while (await_game_tick(p_game));
        manage_game__pre_render(p_game);
        manage_world(p_game);

        poll_ui_manager__update(
                &p_game->gfx_context.ui_manager, 
                p_game, 
                &p_PLATFORM_gfx_context->SDL_graphics_window__main);

        render_graphic_windows_in__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(p_gfx_context), 
                get_p_world_from__game(p_game));

        manage_game__post_render(p_game);
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
