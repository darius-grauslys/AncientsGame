#ifndef NDS_BACKGROUND_H
#define NDS_BACKGROUND_H

#include <defines.h>

static void inline NDS_initialize_background(
        NDS_Background *background) {
    background->background_index = -1;
    background->gfx_map = 0;
    background->gfx_tileset = 0;
    background->background__scroll_x =
        background->background__scroll_y = 0;
    background->priority = 0;
    background->tile_base =
        background->map_base = 0;
}

static void inline NDS_initialize_background_ground__for_game(
        NDS_Background *background) {
    debug_warning("nds_defines init's use magic numbers.");
    background->map_base = 0;
    background->tile_base = 2;
    background->background_index =
        bgInit(1, BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index);
}

static void inline NDS_initialize_background_ground__overlay__for_game(
        NDS_Background *background) {
    debug_warning("nds_defines init's use magic numbers.");
    background->map_base = 4;
    background->tile_base = 2;
    background->background_index =
        bgInit(2, BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index);
}

static void inline NDS_initialize_background_ground__sprite_cover__for_game(
        NDS_Background *background) {
    debug_warning("nds_defines init's use magic numbers.");
    background->map_base = 8;
    background->tile_base = 2;
    background->background_index =
        bgInit(3, BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index);
}

static void inline NDS_initialize_background_ui(
        NDS_Background *background,
        Quantity__u8 layer) {
    debug_warning("nds_defines init's use magic numbers.");
    background->map_base = layer;
    background->tile_base = 1;
    background->background_index =
        bgInitSub(
                layer, 
                BgType_Text8bpp, 
                BgSize_T_256x256, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index);
}

static void inline NDS_initialize_background_ui_for__text_log(
        NDS_Background *background,
        Quantity__u8 layer) {
    debug_warning("nds_defines init's use magic numbers.");
    background->map_base = layer * 2;
    background->tile_base = layer * 2;
    background->background_index =
        bgInitSub(
                layer, 
                BgType_Text8bpp, 
                BgSize_T_256x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index);
}

static void inline NDS_set_background_priority(
        NDS_Background *background,
        uint32_t priority) {
    background->priority = priority;
	bgSetPriority(background->background_index, priority);
}

#endif
