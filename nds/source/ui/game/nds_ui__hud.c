#include <ui/game/nds_ui__hud.h>
#include <nds/arm9/background.h>
#include <defines.h>
#include "defines_weak.h"
#include "entity/reserves.h"
#include <scene/scene__game.h>
#include <timer.h>
#include <entity/humanoid.h>

#include <assets/ui/default/ui_map_hud.h>

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
        Scene *p_scene,
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
        get_hud_timer_from__scene__game(p_scene);
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

void NDS_update_ui_for__hud(
        PLATFORM_Gfx_Context *p_gfx_context,
        Scene *p_scene,
        Entity *p_player) {
    TileMapEntry16 *p_ui_overlay__tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__sub[1]
                .background_index_from__hardware);
    TileMapEntry16 *p_ui__tile_map =
        (TileMapEntry16*)
        bgGetMapPtr(p_gfx_context
                ->backgrounds__sub[0]
                .background_index_from__hardware);

    update_ui_hearts(
            p_player,
            p_ui_overlay__tile_map,
            p_ui__tile_map);

    update_ui_energy_orbs(
            p_player,
            p_ui_overlay__tile_map,
            p_ui__tile_map);

    update_ui_homeostasis(
            p_scene,
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

void NDS_put_hud_onto__background(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        NDS_Background *p_NDS_background) {
    //TODO: magic num, 288 corresponds to the
    //number of map tile indices we are copying.
    dmaCopy(ui_map_hudMap,
            p_NDS_background->gfx_map,
            288 * 2);
}
