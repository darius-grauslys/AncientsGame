#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "debug/nds_debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "entity/handlers/entity_handlers.h"
#include "entity/humanoid.h"
#include "game.h"
#include "game_action/game_action.h"
#include "input/input.h"
#include "nds/arm9/background.h"
#include "platform_defines.h"
#include "rendering/nds_gfx_context.h"
#include "scene/scene_manager.h"
#include "ui/game/nds_ui__hud.h"
#include "ui/nds_ui.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "world/chunk_manager.h"
#include <scene/scene__game.h>
#include <stdint.h>
#include <timer.h>
#include <vectors.h>

#include <assets/ui/default/ui_tileset_default.h>

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
}

void m_ui_button__clicked_handler__game_button(
        UI_Element *p_this_button, Game *p_game) {
    enum Game_Scene_UI_State state =
        *((enum Game_Scene_UI_State*)p_this_button->p_ui_data);
    if (state == scene_data__game.ui_state) {
        NDS_set_ui_background_to__equip(&p_game->gfx_context);
        return;
    }
    switch (state) {
        default:
        case Game_Scene_UI_State__Equip:
            NDS_set_ui_background_to__equip(&p_game->gfx_context);
            break;
        case Game_Scene_UI_State__Ground:
            NDS_set_ui_background_to__ground(&p_game->gfx_context);
            break;
        case Game_Scene_UI_State__Work:
            NDS_set_ui_background_to__work(&p_game->gfx_context);
            break;
    }
}

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    PLATFORM_Gfx_Context *gfx_context =
        &p_game->gfx_context;

    NDS_initialize_gfx_for__world(gfx_context);
    initialize_world(&p_game->world);

    // NDS_initialize_debug__sub();
    // return;
    NDS_initialize_gfx_for__ui(&p_game->gfx_context);
    NDS_set_ui_background_to__equip(&p_game->gfx_context);

    release_all__ui_elements_from__ui_manager(
            &p_game->ui_manager);

    get_many_new__ui_elements_from__ui_manager(
            &p_game->ui_manager, 
            scene_data__game.p_ui_state_buttons, 
            3);

    for (Quantity__u8 ui_index=0;
            ui_index<3;
            ui_index++) {
        UI_Element *p_ui_button = 
            scene_data__game.p_ui_state_buttons[ui_index];
        initialize_ui_element_as__button(
                p_ui_button,
                104, 32,
                get_vector__3i32(56 + 72 * ui_index, 52, 0));
        p_ui_button->p_ui_data =
            &scene_data__game.button_states[ui_index];
        scene_data__game.button_states[ui_index] =
            (enum Game_Scene_UI_State)(ui_index+1);
        set_ui_element__clicked_handler(
                p_ui_button, 
                m_ui_button__clicked_handler__game_button);
    }
}

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {

    // TODO: prob wanna remove some of the stuff below
    Entity *p_player = 
        allocate_entity_into__world(
            &p_game->world,
            Entity_Kind__Player,
            get_vector__3i32F4_using__i32(0, 0, 0));

    p_game->world.entity_manager
        .p_local_player =
        p_player;

    set_camera_to__track_this__entity(
            &p_game->world.camera, 
            p_player);

    move_chunk_manager(
            &p_game->world.chunk_manager, 
            &p_game->world.world_parameters, 
            DIRECTION__NORTH_WEST,
            2);

    PLATFORM_update_chunks(
            &p_game->gfx_context,
            &p_game->world.chunk_manager);

    while (1) {
        if (p_game->scene_manager.p_active_scene == 0)
            break;
        manage_game(p_game);
        NDS_update_ui_for__hud(
                &p_game->gfx_context,
                p_this_scene,
                p_player);
        manage_world(p_game);
    }
}

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    //TODO: impl
    debug_error("not impl, unload game");
}
