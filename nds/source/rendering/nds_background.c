#include "nds_defines.h"
#include <rendering/nds_background.h>

void NDS_initialize_background(
        NDS_Background *background,
        Signed_Index__i8 background_index_for__initializer) {
    background->background_index_from__initializer = 
        background_index_for__initializer;
    background->background_index_from__hardware = -1;
    background->gfx_map = 0;
    background->gfx_tileset = 0;
    background->background__scroll_x =
        background->background__scroll_y = 0;
    background->priority = 0;
    background->tile_base =
        background->map_base = 0;
}

void NDS_initialize_background_for__world_ground(
        NDS_Background *background) {
    debug_warning("nds_background.c init's use magic numbers.");
    background->map_base = 0;
    background->tile_base = 2;
    background->background_index_from__hardware =
        bgInit(background->background_index_from__initializer, 
                BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index_from__hardware);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index_from__hardware);
}

void NDS_initialize_background_for__world_wall_lower(
        NDS_Background *background) {
    debug_warning("nds_background.c init's use magic numbers.");
    background->map_base = 4;
    background->tile_base = 2;
    background->background_index_from__hardware =
        bgInit(background->background_index_from__initializer, 
                BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index_from__hardware);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index_from__hardware);
}

void NDS_initialize_background_for__world_wall_upper(
        NDS_Background *background) {
    debug_warning("nds_background.c init's use magic numbers.");
    background->map_base = 8;
    background->tile_base = 2;
    background->background_index_from__hardware =
        bgInit(background->background_index_from__initializer, 
                BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index_from__hardware);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index_from__hardware);
}

void NDS_initialize_background_with__allocation_specification(
        NDS_Background *p_background,
        NDS_Background_Allocation_Specification
            *p_background_allocation_specification) {
    Signed_Index__i8 layer =
        p_background_allocation_specification
        ->background_slot;

    switch (p_background_allocation_specification
            ->the_kind_of__background_allocation) {
        default:
            p_background->map_base = layer;
            p_background->tile_base = 1;
            p_background->background_index_from__hardware =
                bgInitSub(
                        p_background->background_index_from__initializer, 
                        BgType_Text8bpp, 
                        BgSize_T_256x256, 
                        p_background->map_base, 
                        p_background->tile_base);
            break;
        case NDS_UI_Background_Allocation_Kind__Log_Lower:
        case NDS_UI_Background_Allocation_Kind__Log_Upper:
            p_background->map_base = layer * 2;
            p_background->tile_base = layer * 2;
            p_background->background_index_from__hardware =
                bgInitSub(
                        layer, 
                        BgType_Text8bpp, 
                        BgSize_T_256x512, 
                        p_background->map_base, 
                        p_background->tile_base);
            break;
    }

    p_background->gfx_map = 
        bgGetMapPtr(p_background->background_index_from__hardware);
    p_background->gfx_tileset = 
        bgGetGfxPtr(p_background->background_index_from__hardware);
}

void NDS_set_background_priority(
        NDS_Background *background,
        uint32_t priority) {
    background->priority = priority;
	bgSetPriority(background->background_index_from__hardware, priority);
}

