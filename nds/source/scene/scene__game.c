#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "debug/nds_debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "entity/humanoid.h"
#include "entity/reserves.h"
#include "game.h"
#include "game_action/game_action.h"
#include "input/input.h"
#include "nds/arm9/background.h"
#include "platform_defines.h"
#include "rendering/nds_gfx_context.h"
#include "scene/scene_manager.h"
#include "ui/nds_ui.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "world/chunk_manager.h"
#include <scene/scene__game.h>
#include <stdint.h>
#include <timer.h>

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
    Timer__u8 hud_notification_timer;
} game_scene_data;

void initialize_scene_as__game(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__game_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_as__game_handler;
    p_scene->m_unload_scene_handler =
        m_unload_scene_as__game_handler;

    p_scene->p_scene_data =
        &game_scene_data;
    initialize_timer_u8(
            &game_scene_data.hud_notification_timer,
            30);
}

void m_ui_button__clicked_handler__game_button(
        UI_Element *p_this_button, Game *p_game) {
    enum Game_Scene_UI_State state =
        *((enum Game_Scene_UI_State*)p_this_button->p_ui_data);
    debug_info("clicked - %d", state);
    if (state == game_scene_data.ui_state) {
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
            game_scene_data.p_ui_state_buttons, 
            3);

    for (Quantity__u8 ui_index=0;
            ui_index<3;
            ui_index++) {
        UI_Element *p_ui_button = 
            game_scene_data.p_ui_state_buttons[ui_index];
        initialize_ui_button(
                p_ui_button,
                52, 32);
        set_hitbox__position_with__3i32F4(
                &p_ui_button->ui_bounding_box__aabb, 
                get_vector__3i32F4_with__3i32(56 + 72 * ui_index, 64, 0));
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

void update_ui_hearts(
        Entity *p_player,
        TileMapEntry16 *p_ui_overlay__tile_map,
        TileMapEntry16 *p_ui__tile_map) {
    TileMapEntry16 *p_ui_hearts_overlay_on__tile_map =
        p_ui_overlay__tile_map + (32 * 3 + 3);
    TileMapEntry16 *p_ui_hearts_on__tile_map =
        p_ui__tile_map + (32 * 3 + 3);
    Index__u16 tile_index = 0;
    for (Index__u8 heart_index=0;
            heart_index 
            < p_player->hearts.max_quantity_of__resource_symbols;
            heart_index++) {
        switch (p_player->hearts.resource_symbols[heart_index]) {
            default:
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
                tile_index = UI_TILE_SHEET_INDEX__HALF_POISON_HEART;
                break;
            case Heart_Kind__Full_Poison:
                tile_index = UI_TILE_SHEET_INDEX__FULL_POISON_HEART;
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
                tile_index = UI_TILE_SHEET_INDEX__IMMORTAL_NORMAL_HEART;
                break;
            case Heart_Kind__Locked:
                tile_index = UI_TILE_SHEET_INDEX__LOCKED_HEART;
                break;
        }
        *(uint16_t*)p_ui_hearts_overlay_on__tile_map =
            tile_index;
        *(uint16_t*)p_ui_hearts_on__tile_map =
            tile_index;

        p_ui_hearts_overlay_on__tile_map++;
        p_ui_hearts_on__tile_map++;
    }
}

void update_ui_energy_orbs(
        Entity *p_player,
        TileMapEntry16 *p_ui_overlay__tile_map,
        TileMapEntry16 *p_ui__tile_map) {
    TileMapEntry16 *p_ui_energy_orbs_overlay_on__tile_map =
        p_ui_overlay__tile_map + (32 * 3 + 19);
    TileMapEntry16 *p_ui_energy_orbs_on__tile_map =
        p_ui__tile_map + (32 * 3 + 19);
    Index__u16 tile_index = 0;
    for (Index__u8 energy_orb_index=0;
            energy_orb_index 
            < p_player->energy_orbs.max_quantity_of__resource_symbols;
            energy_orb_index++) {
        tile_index = 0;
        switch (p_player->energy_orbs.resource_symbols[energy_orb_index]) {
            default:
            case Energy_Orb_Kind__Empty:
                tile_index = UI_TILE_SHEET_INDEX__EMPTY_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Half_Normal:
                tile_index = UI_TILE_SHEET_INDEX__HALF_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Full_Normal:
                tile_index = UI_TILE_SHEET_INDEX__FULL_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Normal_Poison:
                tile_index = UI_TILE_SHEET_INDEX__NORMAL_POISON_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Half_Poison:
                tile_index = UI_TILE_SHEET_INDEX__HALF_POISON_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Full_Poison:
                tile_index = UI_TILE_SHEET_INDEX__FULL_POISON_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Demonic_Poison:
                tile_index = UI_TILE_SHEET_INDEX__DEMONIC_POISON_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Half_Demonic:
                tile_index = UI_TILE_SHEET_INDEX__HALF_DEMONIC_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Full_Demonic:
                tile_index = UI_TILE_SHEET_INDEX__FULL_DEMONIC_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Demonic_Normal:
                tile_index = UI_TILE_SHEET_INDEX__DEMONIC_NORMAL_ENERGY_ORB;
                break;
            case Energy_Orb_Kind__Locked:
                tile_index = UI_TILE_SHEET_INDEX__LOCKED_ENERGY_ORB;
                break;
        }
        *(uint16_t*)p_ui_energy_orbs_overlay_on__tile_map =
            tile_index;
        *(uint16_t*)p_ui_energy_orbs_on__tile_map =
            tile_index;

        p_ui_energy_orbs_overlay_on__tile_map++;
        p_ui_energy_orbs_on__tile_map++;
    }
}

void update_ui_homeostasis(
        Scene *p_this_scene,
        Entity *p_player,
        TileMapEntry16 *p_ui_overlay__tile_map,
        TileMapEntry16 *p_ui__tile_map) {
    TileMapEntry16 *p_ui_homeostasis_overlay_on__tile_map =
        p_ui_overlay__tile_map + (32 * 3 + 15);
    TileMapEntry16 *p_ui_homeostasis_on__tile_map =
        p_ui__tile_map + (32 * 3 + 15);
    Index__u16 tile_index = 0;
    enum Homeostasis_State state_of__homeostasis =
        get_state_of__homeostasis_of__entity(p_player);

    switch (state_of__homeostasis) {
        case Homeostasis_State__Extreme_Burning:
            tile_index = UI_TILE_SHEET_INDEX__EXTREME_BURNING;
            break;
        case Homeostasis_State__Burning:
            tile_index = UI_TILE_SHEET_INDEX__BURNING;
            break;
        case Homeostasis_State__Hot:
            tile_index = UI_TILE_SHEET_INDEX__HOT;
            break;
        default:
        case Homeostasis_State__Neutral:
            tile_index = UI_TILE_SHEET_INDEX__NEUTRAL;
            break;
        case Homeostasis_State__Cold:
            tile_index = UI_TILE_SHEET_INDEX__COLD;
            break;
        case Homeostasis_State__Freezing:
            tile_index = UI_TILE_SHEET_INDEX__FREEZING;
            break;
        case Homeostasis_State__Extreme_Freezing:
            tile_index = UI_TILE_SHEET_INDEX__EXTREME_FREEZING;
            break;
        case Homeostasis_State__Divine_Providence:
            tile_index = UI_TILE_SHEET_INDEX__DIVINE_PROVIDENCE;
            break;
        case Homeostasis_State__Soulfull:
            tile_index = UI_TILE_SHEET_INDEX__SOULFULL;
            break;
        case Homeostasis_State__Fleeting_Soul:
            tile_index = UI_TILE_SHEET_INDEX__FLEETING_SOUL;
            break;
        case Homeostasis_State__Soulless:
            tile_index = UI_TILE_SHEET_INDEX__SOULLESS;
            break;
        case Homeostasis_State__Lichling:
            tile_index = UI_TILE_SHEET_INDEX__LICHLING;
            break;
        case Homeostasis_State__Lich:
            tile_index = UI_TILE_SHEET_INDEX__LICH;
            break;
    }

    Timer__u8 *timer = 
            &((struct Game_Scene_Data_t *)p_this_scene->p_scene_data)
                ->hud_notification_timer;
    Quantity__u8 timer_value =
        timer->remaining__u8;
    poll_timer_u8(timer);

    switch (p_player->kind_of_homeostasis__update) {
        default:
        case Homeostasis_Update_Kind__None:
        case Homeostasis_Update_Kind__Unknown:
            break;
        case Homeostasis_Update_Kind__Decreasing:
        case Homeostasis_Update_Kind__Increasing:
            if (state_of__homeostasis 
                    == Homeostasis_State__Extreme_Freezing)
                break;
            if (state_of__homeostasis
                    == Homeostasis_State__Extreme_Burning)
                break;
            switch (p_player->kind_of_homeostasis__update) {
                default:
                case Homeostasis_Update_Kind__Decreasing:
                    tile_index -= 2;
                    break;
                case Homeostasis_Update_Kind__Increasing:
                    tile_index += 2;
                    break;
            }
            if (timer_value > 0 && timer_value < 10) {
                p_player->kind_of_homeostasis__update =
                    Homeostasis_Update_Kind__None;
            } else if (timer_value == 0) {
                reset_timer_u8(timer);
            } 
            break;
    }

    *(uint16_t*)p_ui_homeostasis_overlay_on__tile_map =
        tile_index;
    *(uint16_t*)p_ui_homeostasis_on__tile_map =
        tile_index;
    *(uint16_t*)++p_ui_homeostasis_overlay_on__tile_map =
        tile_index+1;
    *(uint16_t*)++p_ui_homeostasis_on__tile_map =
        tile_index+1;
}

void update_ui_sustenance_primary_as__bloated(
        Entity *p_player,
        TileMapEntry16 *p_ui_overlay__tile_map,
        TileMapEntry16 *p_ui__tile_map) {
    TileMapEntry16 *p_ui_sustenance_primary_overlay_on__tile_map =
        p_ui_overlay__tile_map + (32 * 4);
    TileMapEntry16 *p_ui_sustenance_primary_on__tile_map =
        p_ui__tile_map + (32 * 4);
    bool is_player__undead =
        is_humanoid__undead(p_player);

    Index__u16 tile_index =
        (is_player__undead)
        ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_BLOATED
        : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_BLOATED
        ;

    *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
        tile_index;
    *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
        tile_index;

    *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
        ++tile_index;
    *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
        tile_index;

    p_ui_sustenance_primary_overlay_on__tile_map += 31;
    p_ui_sustenance_primary_on__tile_map += 31;

    tile_index += 7;

    for (Quantity__u8 step=0;step<3;step++) {
        // we do a little loop unrolling
        // we do a little loop unrolling
        *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
            tile_index;
        *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
            tile_index;
        *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
            ++tile_index;
        *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
            tile_index;
        *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
            ++tile_index;
        *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
            tile_index;

        p_ui_sustenance_primary_overlay_on__tile_map += 30;
        p_ui_sustenance_primary_on__tile_map += 30;

        tile_index += 8 * 2;
    }

    tile_index =
        (is_player__undead)
        ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_DESPERATE
        : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_DESPERATE
        ;

    *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
        tile_index;
    *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
        tile_index;
    *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
        ++tile_index;
    *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
        tile_index;
}

void update_ui_sustenance_primary(
        Entity *p_player,
        TileMapEntry16 *p_ui_overlay__tile_map,
        TileMapEntry16 *p_ui__tile_map) {
    TileMapEntry16 *p_ui_sustenance_primary_overlay_on__tile_map =
        p_ui_overlay__tile_map + (32 * 4);
    TileMapEntry16 *p_ui_sustenance_primary_on__tile_map =
        p_ui__tile_map + (32 * 4);
    Index__u16 tile_index = 0;
    bool is_player__undead =
        is_humanoid__undead(p_player);

    update_ui_sustenance_primary_as__bloated(
            p_player, 
            p_ui_overlay__tile_map, 
            p_ui__tile_map);

    enum Sustenance_State state_of__sustenance =
        get_state_of__sustenance_of__entity(
                p_player, 
                Sustenance_Kind__Primary);

    switch (state_of__sustenance) {
        case Sustenance_State__Dying:
        case Sustenance_State__Desperate:
            p_ui_sustenance_primary_overlay_on__tile_map += 32 * 3;
            p_ui_sustenance_primary_on__tile_map += 32 * 3;
            break;
        case Sustenance_State__Wanting:
        case Sustenance_State__Needing:
            p_ui_sustenance_primary_overlay_on__tile_map += 32 * 2;
            p_ui_sustenance_primary_on__tile_map += 32 * 2;
            break;
        case Sustenance_State__Indifferent:
        case Sustenance_State__Well:
            p_ui_sustenance_primary_overlay_on__tile_map += 32;
            p_ui_sustenance_primary_on__tile_map += 32;
            break;
        default:
        case Sustenance_State__Satisifed:
        case Sustenance_State__Full:
        case Sustenance_State__Bloated:
            break;
    }

    switch (state_of__sustenance) {
        case Sustenance_State__Bloated:
            break;
        case Sustenance_State__Dying:
        case Sustenance_State__Desperate:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_BOTTOM_MIDDLE
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_BOTTOM_MIDDLE
                ;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            p_ui_sustenance_primary_overlay_on__tile_map -= 34;
            p_ui_sustenance_primary_on__tile_map -= 34;
        case Sustenance_State__Wanting:
        case Sustenance_State__Needing:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_MIDDLE
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_MIDDLE
                ;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            p_ui_sustenance_primary_overlay_on__tile_map -= 34;
            p_ui_sustenance_primary_on__tile_map -= 34;
        case Sustenance_State__Indifferent:
        case Sustenance_State__Well:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_TOP_MIDDLE
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_TOP_MIDDLE
                ;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            p_ui_sustenance_primary_overlay_on__tile_map -= 34;
            p_ui_sustenance_primary_on__tile_map -= 34;
        default:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_TOP
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_TOP
                ;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
    }

    p_ui_sustenance_primary_overlay_on__tile_map--;
    p_ui_sustenance_primary_on__tile_map--;

    switch (state_of__sustenance) {
        default:
            break;
        case Sustenance_State__Satisifed:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_SATISFIED
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_SATISFIED
                ;
            p_ui_sustenance_primary_overlay_on__tile_map += 32;
            p_ui_sustenance_primary_on__tile_map += 32;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            break;
        case Sustenance_State__Indifferent:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_INDIFFERENT
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_INDIFFERENT
                ;
            p_ui_sustenance_primary_overlay_on__tile_map += 32 * 2;
            p_ui_sustenance_primary_on__tile_map += 32 * 2;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            break;
        case Sustenance_State__Needing:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_NEEDING
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_NEEDING
                ;
            p_ui_sustenance_primary_overlay_on__tile_map += 32 * 3;
            p_ui_sustenance_primary_on__tile_map += 32 * 3;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            break;
        case Sustenance_State__Dying:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BRAIN_EMPTY_BOTTOM
                : UI_TILE_SHEET_INDEX__SUSTENANCE__STOMACH_EMPTY_BOTTOM
                ;
            p_ui_sustenance_primary_overlay_on__tile_map += 32 * 4;
            p_ui_sustenance_primary_on__tile_map += 32 * 4;
            *(uint16_t*)p_ui_sustenance_primary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_primary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_primary_on__tile_map) =
                tile_index;
            break;
    }
}

void update_ui_sustenance_secondary_as__bloated(
        Entity *p_player,
        TileMapEntry16 *p_ui_overlay__tile_map,
        TileMapEntry16 *p_ui__tile_map) {
    TileMapEntry16 *p_ui_sustenance_secondary_overlay_on__tile_map =
        p_ui_overlay__tile_map + (32 * 5) - 2;
    TileMapEntry16 *p_ui_sustenance_secondary_on__tile_map =
        p_ui__tile_map + (32 * 5) - 2;
    bool is_player__undead =
        is_humanoid__undead(p_player);

    Index__u16 tile_index =
        (is_player__undead)
        ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_BLOATED
        : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_BLOATED
        ;

    *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
        tile_index;
    *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
        tile_index;

    *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
        ++tile_index;
    *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
        tile_index;

    p_ui_sustenance_secondary_overlay_on__tile_map += 30;
    p_ui_sustenance_secondary_on__tile_map += 30;

    tile_index += 8;

    for (Quantity__u8 step=0;step<3;step++) {
        // we do a little loop unrolling
        // we do a little loop unrolling
        *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
            tile_index;
        *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
            tile_index;
        *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
            ++tile_index;
        *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
            tile_index;
        *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
            ++tile_index;
        *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
            tile_index;

        p_ui_sustenance_secondary_overlay_on__tile_map += 30;
        p_ui_sustenance_secondary_on__tile_map += 30;

        tile_index += 8 * 2;
    }

    p_ui_sustenance_secondary_overlay_on__tile_map++;
    p_ui_sustenance_secondary_on__tile_map++;

    tile_index =
        (is_player__undead)
        ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_DESPERATE
        : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_DESPERATE
        ;

    *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
        tile_index;
    *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
        tile_index;
    *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
        ++tile_index;
    *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
        tile_index;
}

void update_ui_sustenance_secondary(
        Entity *p_player,
        TileMapEntry16 *p_ui_overlay__tile_map,
        TileMapEntry16 *p_ui__tile_map) {
    TileMapEntry16 *p_ui_sustenance_secondary_overlay_on__tile_map =
        p_ui_overlay__tile_map + (32 * 5) - 2;
    TileMapEntry16 *p_ui_sustenance_secondary_on__tile_map =
        p_ui__tile_map + (32 * 5) - 2;
    Index__u16 tile_index = 0;
    bool is_player__undead =
        is_humanoid__undead(p_player);

    update_ui_sustenance_secondary_as__bloated(
            p_player, 
            p_ui_overlay__tile_map, 
            p_ui__tile_map);

    enum Sustenance_State state_of__sustenance =
        get_state_of__sustenance_of__entity(
                p_player, 
                Sustenance_Kind__Secondary);

    switch (state_of__sustenance) {
        case Sustenance_State__Dying:
        case Sustenance_State__Desperate:
            p_ui_sustenance_secondary_overlay_on__tile_map += 32 * 3 - 1;
            p_ui_sustenance_secondary_on__tile_map += 32 * 3 - 1;
            break;
        case Sustenance_State__Wanting:
        case Sustenance_State__Needing:
            p_ui_sustenance_secondary_overlay_on__tile_map += 32 * 2 - 1;
            p_ui_sustenance_secondary_on__tile_map += 32 * 2 - 1;
            break;
        case Sustenance_State__Indifferent:
        case Sustenance_State__Well:
            p_ui_sustenance_secondary_overlay_on__tile_map += 32 - 1;
            p_ui_sustenance_secondary_on__tile_map += 32 - 1;
            break;
        default:
        case Sustenance_State__Satisifed:
        case Sustenance_State__Full:
        case Sustenance_State__Bloated:
            break;
    }

    switch (state_of__sustenance) {
        case Sustenance_State__Bloated:
            break;
        case Sustenance_State__Dying:
        case Sustenance_State__Desperate:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_BOTTOM_MIDDLE
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_BOTTOM_MIDDLE
                ;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            p_ui_sustenance_secondary_overlay_on__tile_map -= 34;
            p_ui_sustenance_secondary_on__tile_map -= 34;
        case Sustenance_State__Wanting:
        case Sustenance_State__Needing:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_MIDDLE
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_MIDDLE
                ;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            p_ui_sustenance_secondary_overlay_on__tile_map -= 34;
            p_ui_sustenance_secondary_on__tile_map -= 34;
        case Sustenance_State__Indifferent:
        case Sustenance_State__Well:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_TOP_MIDDLE
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_TOP_MIDDLE
                ;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            p_ui_sustenance_secondary_overlay_on__tile_map -= 33;
            p_ui_sustenance_secondary_on__tile_map -= 33;
        default:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_TOP
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_TOP
                ;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            p_ui_sustenance_secondary_overlay_on__tile_map--;
            p_ui_sustenance_secondary_on__tile_map--;
    }

    p_ui_sustenance_secondary_overlay_on__tile_map--;
    p_ui_sustenance_secondary_on__tile_map--;

    switch (state_of__sustenance) {
        default:
            break;
        case Sustenance_State__Satisifed:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_SATISFIED
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_SATISFIED
                ;
            p_ui_sustenance_secondary_overlay_on__tile_map += 32;
            p_ui_sustenance_secondary_on__tile_map += 32;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            break;
        case Sustenance_State__Indifferent:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_INDIFFERENT
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_INDIFFERENT
                ;
            p_ui_sustenance_secondary_overlay_on__tile_map += 32 * 2;
            p_ui_sustenance_secondary_on__tile_map += 32 * 2;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            break;
        case Sustenance_State__Needing:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_NEEDING
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_NEEDING
                ;
            p_ui_sustenance_secondary_overlay_on__tile_map += 32 * 3;
            p_ui_sustenance_secondary_on__tile_map += 32 * 3;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            break;
        case Sustenance_State__Dying:
            tile_index = 
                (is_player__undead)
                ? UI_TILE_SHEET_INDEX__SUSTENANCE__BLOOD_EMPTY_BOTTOM
                : UI_TILE_SHEET_INDEX__SUSTENANCE__THIRST_EMPTY_BOTTOM
                ;
            p_ui_sustenance_secondary_overlay_on__tile_map += 32 * 4 + 1;
            p_ui_sustenance_secondary_on__tile_map += 32 * 4 + 1;
            *(uint16_t*)p_ui_sustenance_secondary_overlay_on__tile_map =
                tile_index;
            *(uint16_t*)p_ui_sustenance_secondary_on__tile_map =
                tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_overlay_on__tile_map) =
                ++tile_index;
            *(uint16_t*)(++p_ui_sustenance_secondary_on__tile_map) =
                tile_index;
            break;
    }
}

void update_ui_for__player_resources(
        Scene *p_this_scene,
        Game *p_game) {
    TileMapEntry16 *p_ui_overlay__tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_game->gfx_context
                .background_ui__overlay
                .background_index);
    TileMapEntry16 *p_ui__tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_game->gfx_context
                .background_ui
                .background_index);

    Entity *p_player =
        p_game->world.entity_manager.p_local_player;
    if (!p_player) {
        //TODO: make a one time log
        p_game->scene_manager.p_active_scene = 0;
        return;
    }

    update_ui_hearts(
            p_player,
            p_ui_overlay__tile_map,
            p_ui__tile_map);

    update_ui_energy_orbs(
            p_player,
            p_ui_overlay__tile_map,
            p_ui__tile_map);

    update_ui_homeostasis(
            p_this_scene, 
            p_player, 
            p_ui_overlay__tile_map, 
            p_ui__tile_map);

    update_ui_sustenance_primary(
            p_player,
            p_ui_overlay__tile_map,
            p_ui__tile_map);

    update_ui_sustenance_secondary(
            p_player,
            p_ui_overlay__tile_map,
            p_ui__tile_map);
}

void m_enter_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game) {

    // TODO: prob wanna remove some of the stuff below
    Entity *p_player = 
        allocate_entity_into__world(
            &p_game->world,
            Entity_Kind__Player,
            get_vector__3i32F4_with__3i32(0, 0, 0));

    p_game->world.entity_manager
        .p_local_player =
        p_player;

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
        if (is_input__game_settings_released(&p_game->input)) {
            invoke_action__increase_homeostasis_of__entity(
                    p_game,
                    p_player,
                    p_player,
                    8);
        }
        if (is_input__lockon_released(&p_game->input)) {
            invoke_action__decrease_homeostasis_of__entity(
                    p_game,
                    p_player,
                    p_player,
                    8);
        }
        if (is_input__consume_released(&p_game->input)) {
            invoke_action__increase_sustenance_of__entity(
                    p_game,
                    p_player,
                    p_player,
                    Sustenance_Kind__Hunger,
                    8);
        }
        if (is_input__examine_released(&p_game->input)) {
            invoke_action__increase_sustenance_of__entity(
                    p_game,
                    p_player,
                    p_player,
                    Sustenance_Kind__Thirst,
                    8);
        }
        if (is_input__use_released(&p_game->input)) {
            Energy_Damaging_Specifier damage;
            damage.energy_damaging__flags = 0;
            damage.quantity_of__damage = 10;
            invoke_action__apply_energy_damage_to__entity(
                    p_game, 
                    p_player, 
                    p_player, 
                    &damage);
        }
        if (is_input__use_secondary_released(&p_game->input)) {
            Hearts_Damaging_Specifier damage;
            damage.hearts_damaging__flags = 0;
            damage.quantity_of__damage = 10;
            invoke_action__apply_heart_damage_to__entity(
                    p_game, 
                    p_player, 
                    p_player, 
                    &damage);
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
