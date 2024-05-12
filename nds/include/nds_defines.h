#ifndef NDS_DEFINES_H
#define NDS_DEFINES_H

#include <nds.h>
#include <debug/debug.h>

static void inline NDS_init_background_ground__for_game(
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
    // bgHide(background->background_index);
}

static void inline NDS_init_background_ground__overlay__for_game(
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
    //bgHide(background->background_index);
}

static void inline NDS_init_background_ui__for_game(
        NDS_Background *background) {
    debug_warning("nds_defines init's use magic numbers.");
    background->map_base = 0;
    background->tile_base = 2;
    background->background_index =
        bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index);
    //bgHide(background->background_index);
}

static void inline NDS_init_background_ui__overlay__for_game(
        NDS_Background *background) {
    debug_warning("nds_defines init's use magic numbers.");
    background->map_base = 4;
    background->tile_base = 2;
    background->background_index =
        bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 
                background->map_base, 
                background->tile_base);
    background->gfx_map = 
        bgGetMapPtr(background->background_index);
    background->gfx_tileset = 
        bgGetGfxPtr(background->background_index);
    //bgHide(background->background_index);
}

static void inline NDS_set_background_priority(NDS_Background *background,
        uint32_t priority) {
    background->priority = priority;
	bgSetPriority(background->background_index, priority);
}

#endif
