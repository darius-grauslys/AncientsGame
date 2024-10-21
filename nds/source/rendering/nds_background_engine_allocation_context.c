#include "defines_weak.h"
#include "nds_defines.h"
#include "rendering/nds_background_allocation_specification.h"
#include "vectors.h"
#include <rendering/nds_background_engine_allocation_context.h>

#include <assets/ui/default/GFX_default.h>
#include <assets/ui/typer/GFX_typer.h>

#include <assets/ui/default/ui_map_idle.h>
#include <assets/ui/default/ui_map_equip.h>
#include <assets/ui/default/ui_map_equipment.h>
#include <assets/ui/default/ui_map_trade.h>
#include <assets/ui/default/ui_map_labor.h>
#include <assets/ui/default/ui_map_inventory_column.h>
#include <assets/ui/default/ui_map_short_inventory_column.h>
#include <assets/ui/default/ui_map_loading.h>
#include <assets/ui/default/ui_map_station.h>
#include <assets/ui/default/ui_map_station_items.h>

#include <assets/ui/log/GFX_log.h>
#include <assets/ui/log/ui_map_log.h>

#include <assets/ui/typer/ui_map_typer__locked.h>
#include <assets/ui/typer/ui_map_typer__lowercase.h>
#include <assets/ui/typer/ui_map_typer__uppercase.h>

#include <assets/ui/default/ui_map_main_menu.h>
#include <assets/ui/default/ui_map_multiplayer.h>
#include <assets/ui/default/ui_map_singleplayer.h>
#include <assets/ui/default/ui_map_settings.h>

bool NDS_does_NOT_bg_alloc_spec_share__palette_with__another_bg_alloc_spec(
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec,
        NDS_Background_Engine_Allocation_Context 
            *p_NDS_bg_engine_alloc_context) {
    for (Index__u8 index=0;
            index < NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
            index++) {
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec__other =
            &p_NDS_bg_engine_alloc_context
            ->nds_background_allocation_specifications[index];
        if (p_NDS_bg_alloc_spec == p_NDS_bg_alloc_spec__other)
            return true;
        if (p_NDS_bg_alloc_spec__other
                ->slot_for__extended_palette
                == p_NDS_bg_alloc_spec
                ->slot_for__extended_palette)
            return false;
    }
    return true;
}

bool NDS_does_NOT_bg_alloc_spec_have_shared_map_offset(
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec,
        NDS_Background_Engine_Allocation_Context 
            *p_NDS_bg_engine_alloc_context) {
    for (Index__u8 index=0;
            index < NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
            index++) {
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec__other =
            &p_NDS_bg_engine_alloc_context
            ->nds_background_allocation_specifications[index];
        if (p_NDS_bg_alloc_spec == p_NDS_bg_alloc_spec__other)
            return true;
        if (p_NDS_bg_alloc_spec__other
                ->offset_for__map
                == p_NDS_bg_alloc_spec
                ->offset_for__map) {
            return false;
        }
    }
    return true;
}

bool NDS_does_NOT_bg_alloc_spec__shared_tileset_offset(
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec,
        NDS_Background_Engine_Allocation_Context 
            *p_NDS_bg_engine_alloc_context) {
    for (Index__u8 index=0;
            index < NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
            index++) {
        NDS_Background_Allocation_Specification *p_NDS_bg_alloc_spec__other =
            &p_NDS_bg_engine_alloc_context
            ->nds_background_allocation_specifications[index];
        if (p_NDS_bg_alloc_spec == p_NDS_bg_alloc_spec__other)
            return true;
        if (p_NDS_bg_alloc_spec__other
                ->offset_for__tileset
                == p_NDS_bg_alloc_spec
                ->offset_for__tileset) {
            return false;
        }
    }
    return true;
}

void NDS_initialize_background_engine_allocation_context(
        NDS_Background_Engine_Allocation_Context
            *p_NDS_background_engine_allocation_context,
        enum UI_Window_Kind the_kind_of__ui_window_to__allocate_for) {

    for (Index__u8 index=0;
            index < NDS_QUANTITY_OF__BACKGROUNDS_PER__ENGINE;
            index++) {
        p_NDS_background_engine_allocation_context
            ->nds_background_allocation_specifications[index] =
            nds_background_allocation_specification__none;
    }

    switch (the_kind_of__ui_window_to__allocate_for) {
        default:
        case UI_Window_Kind__Idle:
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__BASE],
                    NDS_UI_Background_Allocation_Kind__Base,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__BASE, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_idleMap, 
                    ui_map_idleMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__BASE);
            NDS_initialize_background_allocation_specification_with__reservations(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__LOG_LOWER],
                    NDS_UI_Background_Allocation_Kind__Log_Lower,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__LOG_LOWER, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_logTiles, 
                    GFX_logTilesLen, 
                    448 << 6,
                    ui_map_logMap, 
                    ui_map_logMapLen,
                    448 << 6,
                    GFX_logPal,
                    GFX_logPalLen,
                    0,
                    NDS_BACKGROUND_PRIORITY__UI__LOG_LOWER);
            NDS_initialize_background_allocation_specification_with__reservations(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__LOG_UPPER],
                    NDS_UI_Background_Allocation_Kind__Log_Upper,
                    TEXTURE_FLAG__SIZE_256x512,
                    NDS_BACKGROUND_SLOT__UI__LOG_UPPER, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_logTiles, 
                    GFX_logTilesLen, 
                    896 << 6,
                    ui_map_logMap, 
                    ui_map_logMapLen,
                    896 << 6,
                    GFX_logPal,
                    GFX_logPalLen,
                    0,
                    NDS_BACKGROUND_PRIORITY__UI__LOG_UPPER);
            // TODO: make a UI_Window_Kind__Chat
            // NDS_initialize_background_allocation_specification_with__reservations(
            //         &p_NDS_background_engine_allocation_context
            //             ->nds_background_allocation_specifications[
            //                 NDS_BACKGROUND_SLOT__UI__TYPER],
            //         NDS_UI_Background_Allocation_Kind__Typer,
            //         TEXTURE_FLAG__SIZE_256x256,
            //         NDS_BACKGROUND_SLOT__UI__TYPER, 
            //         VECTOR__3i32__0_0_0,
            //         VECTOR__3i32__0_0_0,
            //         GFX_typerTiles, 
            //         GFX_typerTilesLen, 
            //         64 << 6,
            //         ui_map_typer__lockedMap, 
            //         ui_map_typer__lockedMapLen,
            //         64 << 6,
            //         GFX_typerPal,
            //         GFX_typerPalLen,
            //         0,
            //         NDS_BACKGROUND_PRIORITY__UI__SCROLL_TYPER);
            break;
        case UI_Window_Kind__Station:
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__BASE],
                    NDS_UI_Background_Allocation_Kind__Base,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__BASE, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_stationMap, 
                    ui_map_stationMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__BASE);
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__SUB_BASE],
                    NDS_UI_Background_Allocation_Kind__Sub_Base,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__SUB_BASE, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_station_itemsMap, 
                    ui_map_station_itemsMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__SUB_BASE);
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__SCROLL],
                    NDS_UI_Background_Allocation_Kind__Scroll,
                    TEXTURE_FLAG__SIZE_256x512,
                    NDS_BACKGROUND_SLOT__UI__SCROLL, 
                    get_vector__3i32(-168, 86, 0),
                    get_vector__3i32(0, 176, 0),
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_short_inventory_columnMap, 
                    ui_map_short_inventory_columnMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__SCROLL);
            break;
        case UI_Window_Kind__Equip:
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__BASE],
                    NDS_UI_Background_Allocation_Kind__Base,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__BASE, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_equipMap, 
                    ui_map_equipMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__BASE);
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__SUB_BASE],
                    NDS_UI_Background_Allocation_Kind__Sub_Base,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__SUB_BASE, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_equipmentMap, 
                    ui_map_equipmentMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__SUB_BASE);
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__SCROLL],
                    NDS_UI_Background_Allocation_Kind__Scroll,
                    TEXTURE_FLAG__SIZE_256x512,
                    NDS_BACKGROUND_SLOT__UI__SCROLL, 
                    get_vector__3i32(-88, 86, 0),
                    get_vector__3i32(0, 176, 0),
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_inventory_columnMap, 
                    ui_map_inventory_columnMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__SCROLL);
            break;
        case UI_Window_Kind__Trade:
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__BASE],
                    NDS_UI_Background_Allocation_Kind__Base,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__BASE, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_tradeMap, 
                    ui_map_tradeMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__BASE);
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__SCROLL],
                    NDS_UI_Background_Allocation_Kind__Scroll,
                    TEXTURE_FLAG__SIZE_256x512,
                    NDS_BACKGROUND_SLOT__UI__SCROLL, 
                    // get_vector__3i32(58, 96, 0),
                    get_vector__3i32(-44, 86, 0),
                    get_vector__3i32(0, 176, 0),
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_inventory_columnMap, 
                    ui_map_inventory_columnMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__SCROLL);
            NDS_initialize_background_allocation_specification(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__SCROLL_SECONDARY],
                    NDS_UI_Background_Allocation_Kind__Scroll_Secondary,
                    TEXTURE_FLAG__SIZE_256x512,
                    NDS_BACKGROUND_SLOT__UI__SCROLL_SECONDARY, 
                    get_vector__3i32(-132, 86, 0),
                    get_vector__3i32(0, 176, 0),
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    ui_map_inventory_columnMap, 
                    ui_map_inventory_columnMapLen,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    NDS_BACKGROUND_PRIORITY__UI__SCROLL_SECONDARY);
            break;
        case UI_Window_Kind__Labor:
            NDS_initialize_background_allocation_specification_with__reservations(
                    &p_NDS_background_engine_allocation_context
                        ->nds_background_allocation_specifications[
                            NDS_BACKGROUND_SLOT__UI__BASE],
                    NDS_UI_Background_Allocation_Kind__Base,
                    TEXTURE_FLAG__SIZE_256x256,
                    NDS_BACKGROUND_SLOT__UI__BASE, 
                    VECTOR__3i32__0_0_0,
                    VECTOR__3i32__0_0_0,
                    GFX_defaultTiles, 
                    GFX_defaultTilesLen, 
                    64 << 6,
                    ui_map_laborMap, 
                    ui_map_laborMapLen,
                    64 << 6,
                    GFX_defaultPal,
                    GFX_defaultPalLen,
                    0,
                    NDS_BACKGROUND_PRIORITY__UI__BASE);
            break;
    }
}
