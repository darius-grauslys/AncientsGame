#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "debug/nds_debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "entity/reserves.h"
#include "game.h"
#include "input/input.h"
#include "nds/arm9/background.h"
#include "rendering/nds_gfx_context.h"
#include "ui/nds_ui.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "world/chunk_manager.h"
#include <scene/scene__game.h>
#include <stdint.h>

#include <assets/ui/_ui_tiles.h>

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

enum Game_Scene_UI_State {
    Game_Scene_UI_State__Idle,
    Game_Scene_UI_State__Equip,
    Game_Scene_UI_State__Ground,
    Game_Scene_UI_State__Work,
};

struct Game_Scene_Data_t {
    enum Game_Scene_UI_State ui_state;
    enum Game_Scene_UI_State button_states[3];
    UI_Element *p_ui_state_buttons[3];
} game_scene_data;

void init_scene_as__game(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__game_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__game_handler;
    p_scene->m_unload_scene_handler =
        m_unload_scene_as__game_handler;

    p_scene->p_scene_data =
        &game_scene_data;
}

void m_ui_button__clicked_handler__game_button(
        UI_Element *p_this_button, Game *p_game) {
    enum Game_Scene_UI_State state =
        *((enum Game_Scene_UI_State*)p_this_button->p_ui_data);
    debug_info("clicked - %d", state);
    if (state == game_scene_data.ui_state) {
        NDS_set_ui_to__equip(&p_game->gfx_context);
        return;
    }
    switch (state) {
        default:
        case Game_Scene_UI_State__Equip:
            NDS_set_ui_to__equip(&p_game->gfx_context);
            break;
        case Game_Scene_UI_State__Ground:
            NDS_set_ui_to__ground(&p_game->gfx_context);
            break;
        case Game_Scene_UI_State__Work:
            NDS_set_ui_to__work(&p_game->gfx_context);
            break;
    }
}

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    PLATFORM_Gfx_Context *gfx_context =
        &p_game->gfx_context;

    NDS_init_gfx_for__world(gfx_context);
    init_world(&p_game->world);

    // NDS_init_debug__sub();
    // return;
    NDS_init_gfx_for__ui(&p_game->gfx_context);
    NDS_set_ui_to__equip(&p_game->gfx_context);

    release_all__ui_elements_from__ui_manager(
            &p_game->ui_manager);

    get_many_new__ui_elements_from__ui_manager(
            &p_game->ui_manager, 
            game_scene_data.p_ui_state_buttons, 
            3);

    for (Quantity__u8 ui_index=0;
            ui_index<3;
            ui_index++) {
        UI_Element *p_ui_button = 
            game_scene_data.p_ui_state_buttons[ui_index];
        init_ui_button(
                p_ui_button,
                52, 32);
        set_hitbox__position(
                &p_ui_button->ui_bounding_box__aabb, 
                56 + 72 * ui_index, 
                64, 
                0);
        p_ui_button->p_ui_data =
            &game_scene_data.button_states[ui_index];
        game_scene_data.button_states[ui_index] =
            (enum Game_Scene_UI_State)(ui_index+1);
        set_ui_element__clicked_handler(
                p_ui_button, 
                m_ui_button__clicked_handler__game_button);

        Vector__3i32F4 aa, bb;
        get_points_aabb_from__hitbox(
                &p_ui_button->ui_bounding_box__aabb, 
                &aa,
                &bb);
    }
}
void update_ui_for__player_resources(
        Scene *p_this_scene,
        Game *p_game) {
    TileMapEntry16 *p_ui_overlay__tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_game->gfx_context
                .background_ui__overlay
                .background_index) + (32 * 3 + 3);
    TileMapEntry16 *p_ui__tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_game->gfx_context
                .background_ui
                .background_index) + (32 * 3 + 3);

    Entity *p_player =
        p_game->world.entity_manager.p_local_player;
    if (!p_player) {
        //TODO: make a one time log
        p_game->scene_manager.p_active_scene = 0;
        return;
    }
    // debug_info("hearts %d", p_player->hearts.max_quantity_of__resource_symbols);
    for (Index__u8 heart_index=0;
            heart_index < p_player->hearts.max_quantity_of__resource_symbols;
            heart_index++) {
        Index__u16 tile_index = 0;
        switch (p_player->hearts.resource_symbols[heart_index]) {
            default:
                //TODO: magic numbers
            case Heart_Kind__Empty:
                tile_index = UI_TILE_SHEET_INDEX__EMPTY_HEART;
                break;
            case Heart_Kind__Half_Normal:
                tile_index = UI_TILE_SHEET_INDEX__HALF_HEART;
                break;
            case Heart_Kind__Full_Normal:
                tile_index = UI_TILE_SHEET_INDEX__FULL_HEART;
                break;
            case Heart_Kind__Normal_Poison:
                tile_index = UI_TILE_SHEET_INDEX__NORMAL_POISON_HEART;
                break;
            case Heart_Kind__Half_Poison:
                //TODO: lost the half poison heart somehow
                tile_index = UI_TILE_SHEET_INDEX__HALF_POISON_HEART;
                break;
            case Heart_Kind__Full_Poison:
                tile_index = UI_TILE_SHEET_INDEX__FULL_HEART;
                break;
            case Heart_Kind__Immortal_Poison:
                tile_index = UI_TILE_SHEET_INDEX__IMMORTAL_POISON_HEART;
                break;
            case Heart_Kind__Half_Immortal:
                tile_index = UI_TILE_SHEET_INDEX__HALF_IMMORTAL_HEART;
                break;
            case Heart_Kind__Full_Immortal:
                tile_index = UI_TILE_SHEET_INDEX__FULL_IMMORTAL_HEART;
                break;
            case Heart_Kind__Immortal_Normal:
                tile_index = UI_TILE_SHEET_INDEX__HALF_IMMORTAL_HEART;
                break;
            case Heart_Kind__Locked:
                tile_index = UI_TILE_SHEET_INDEX__LOCKED_HEART;
                break;
        }
        *(uint16_t*)p_ui_overlay__tile_map =
            tile_index;
        *(uint16_t*)p_ui__tile_map =
            tile_index;

        p_ui_overlay__tile_map++;
        p_ui__tile_map++;
    }
}

uint16_t _index_tmp = 0;
void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {

    // TODO: prob wanna remove some of the stuff below
    add_entity_to__world(
            &p_game->world,
            Entity_Kind__Player,
            0, 0, 0);
    get_new__entity(
            &p_game->world.entity_manager, 
            Entity_Kind__Player,
            0, 0, 0);

    move_chunk_manager(
            &p_game->world.chunk_manager, 
            &p_game->world.world_parameters, 
            DIRECTION__NORTH_WEST,
            2);

    PLATFORM_update_chunks(
            &p_game->gfx_context,
            &p_game->world.chunk_manager);

    Hearts_Healing_Specifier healing;
    healing.hearts_healing__flags = 0;
    healing.quantity_of__healing = 1;

    while (1) {
        if (p_game->scene_manager.p_active_scene == 0)
            break;
        manage_game(p_game);
        if (is_input__click_released(&p_game->input)) {
            debug_info("input %d, %d",
                    p_game->input.cursor__old__i32f4.x__i32F4,
                    p_game->input.cursor__old__i32f4.y__i32F4
                    );
        }
        if (is_input__consume_released(&p_game->input)) {
            apply_hearts_healing_specifier_to__entity(
                    p_game->world.entity_manager.p_local_player, 
                    healing);
        }
        update_ui_for__player_resources(
                p_this_scene, 
                p_game);
        manage_world(p_game);
    }
}

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {
    //TODO: impl
    debug_error("not impl, unload game");
}
