#include <ui/game/nds_ui__trade.h>
#include <nds.h>
#include <platform_defines.h>
#include <assets/ui/default/ui_map_trade.h>
#include <assets/ui/default/GFX_default.h>
#include <ui/game/nds_ui__hud.h>

void NDS_set_ui_container_to__ground(
        UI_Element *p_ui_container) {

}

void NDS_set_ui_background_to__ground(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(GFX_defaultTiles, 
            p_gfx_context->background_ui
            .gfx_tileset, GFX_defaultTilesLen);
	dmaCopy(GFX_defaultTiles, 
            p_gfx_context->background_ui__overlay
            .gfx_tileset, GFX_defaultTilesLen);
	dmaCopy(ui_map_tradeMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_tradeMapLen);
	dmaCopy(ui_map_tradeMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_tradeMapLen);
    NDS_put_hud_onto__background(
            p_gfx_context,
            &p_gfx_context->background_ui);
    NDS_put_hud_onto__background(
            p_gfx_context,
            &p_gfx_context->background_ui__overlay);
}
