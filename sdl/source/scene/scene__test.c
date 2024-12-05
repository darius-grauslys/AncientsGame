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
#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_shader_passthrough.h"
#include "rendering/opengl/gl_vertex_object.h"
#include "rendering/sdl_chunk.h"
#include "rendering/sdl_gfx_context.h"
#include "rendering/sdl_gfx_window_manager.h"
#include "rendering/sdl_render_world.h"
#include "sdl_defines.h"
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
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {

    initialize_world(
            p_game,
            get_p_world_from__game(p_game),
            SDL_get_main_graphics_window_from__gfx_context(
                get_p_PLATFORM_gfx_context_from__game(p_game)));
    load_world(p_game);
    while(!get_p_local_player_from__game(p_game)) {
        manage_game__pre_render(p_game); // handle loading first.
    }
    Entity *p_player = 
        p_game->world.entity_manager
            .p_local_player;
    set_camera_to__track_this__entity(
            p_game
            ->p_PLATFORM_gfx_context
            ->SDL_graphics_window__main
            .p_active_camera,
            p_player);
    teleport_player(
            p_game, 
            get_p_local_player_from__game(p_game)
            ->hitbox.position__3i32F4);

    get_p_local_player_from__game(p_game)
        ->equipment
        .item_stack__main_hand
        .item =
            get_item_from__item_manager(
                get_p_item_manager_from__game(p_game), 
                Item_Kind__Hammer__Iron);

    get_p_local_player_from__game(p_game)
        ->equipment
        .item_stack__main_hand
        .quantity_of__items = 1;
    get_p_local_player_from__game(p_game)
        ->equipment
        .item_stack__main_hand
        .max_quantity_of__items = 1;

    get_p_local_player_from__game(p_game)
        ->equipment
        .item_stack__off_hand
        .item =
            get_item_from__item_manager(
                get_p_item_manager_from__game(p_game), 
                Item_Kind__Pile__Dirt__Plenty);

    get_p_local_player_from__game(p_game)
        ->equipment
        .item_stack__main_hand
        .quantity_of__items = 1;
    get_p_local_player_from__game(p_game)
        ->equipment
        .item_stack__main_hand
        .max_quantity_of__items = 1;

    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game),
            get_p_chunk_manager_from__game(p_game));

    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game__pre_render(p_game);

        /// --- do better --- TODO:
        PLATFORM_Graphics_Window *ptr_array_of__gfx_windows[
            PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF];
        Signed_Quantity__i32 quantity_of__windows =
            SDL_get_p_PLATFORM_gfx_windows_by__type_from__manager(
                    SDL_get_p_gfx_window_manager_from__PLATFORM_gfx_context(
                        get_p_PLATFORM_gfx_context_from__game(
                            p_game)), 
                    UI_Window_Kind__Unknown, 
                    ptr_array_of__gfx_windows, 
                    PLATFORM__GFX_WINDOW__MAX_QUANTITY_OF);
        if (quantity_of__windows) {
            consume_input(
                    get_p_input_from__game(p_game),
                    INPUT_USE);
        }
        // --- up to here ---

        SDL_render_world(p_game);

        if (is_input__game_settings_released(
                    get_p_input_from__game(p_game))) {
            PLATFORM_close_ui(
                    p_game, 
                    UI_Window_Kind__Unknown);
        }
        if (SDL_is_input__equip_released(
                    get_p_input_from__game(p_game))) {
            PLATFORM_open_ui(
                    p_game, 
                    UI_Window_Kind__Equip, 
                    0);
        }
        manage_game__post_render(p_game);
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
