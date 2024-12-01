#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "debug/nds_debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "entity/entity_manager.h"
#include "entity/handlers/entity_handlers.h"
#include "entity/humanoid.h"
#include "game.h"
#include "game_action/game_action.h"
#include "input/input.h"
#include "inventory/inventory.h"
#include "inventory/inventory_manager.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "nds/arm9/background.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/sprite.h"
#include "scene/scene_manager.h"
#include "ui/game/nds_ui_background__game__hud.h"
#include "ui/nds_ui.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "world/chunk.h"
#include "world/chunk_manager.h"
#include "world/serialization/world_directory.h"
#include "world/tile.h"
#include "world/tile_vectors.h"
#include "world/world.h"
#include <scene/nds_scene__game.h>
#include <stdint.h>
#include <timer.h>
#include <vectors.h>
#include <rendering/gfx_context.h>

Scene_Data__Game scene_data__game;

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void initialize_scene_as__game(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__game_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__game_handler;
    p_scene->m_unload_scene_handler =
        m_unload_scene_as__game_handler;

    p_scene->p_scene_data =
        &scene_data__game;

    //TODO: magic number
    initialize_timer_u8(
            &scene_data__game
            .timer_for__hud_notification__u8,
            30);
    initialize_timer_u8(
            &scene_data__game
            .timer_for__typer_sliding__u8,
            16);
}

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    NDS_initialize_gfx_for__world(p_gfx_context);
    initialize_world(
            p_game,
            get_p_world_from__game(p_game),
            NDS_get_graphics_window__main_from__gfx_context(
                get_p_PLATFORM_gfx_context_from__game(p_game)));
    load_world(p_game);
    while(!get_p_local_player_from__game(p_game)) {
        manage_game__post_render(p_game); // handle loading first.
    }
    teleport_player(
            p_game, 
            get_p_local_player_from__game(p_game)
            ->hitbox.position__3i32F4);
    set_camera_to__track_this__entity(
            &p_game->world.camera, 
            get_p_local_player_from__game(p_game));
    PLATFORM_update_chunks(
            get_p_PLATFORM_gfx_context_from__game(p_game),
            get_p_chunk_manager_from__game(p_game));

    // NDS_initialize_debug__sub();
    // return;
    NDS_initialize_gfx_for__ui(
            get_p_PLATFORM_gfx_context_from__game(p_game));
    // TODO: re-impl
    // NDS_set_ui_background_to__equip(&p_game->gfx_context);

    PLATFORM_open_ui(
            p_game,
            UI_Window_Kind__Idle,
            0);
}

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {

    // TODO: prob wanna remove some of the stuff below
    Entity *p_player = 
        get_p_local_player_from__game(p_game);

    while (1) {
        if (p_game->scene_manager.p_active_scene == 0)
            break;
        manage_game__pre_render(p_game);
        NDS_update_ui_for__hud(
                get_p_PLATFORM_gfx_context_from__game(p_game),
                p_this_scene,
                p_player);
        if (is_input__consume_released(
                    get_p_input_from__game(p_game))) {
            save_world(p_game);
        }
        manage_world(p_game);
        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    //TODO: impl
    debug_error("not impl, unload game");
}
