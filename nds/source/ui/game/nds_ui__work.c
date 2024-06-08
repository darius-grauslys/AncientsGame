#include <ui/game/nds_ui__work.h>
#include <assets/ui/ui_map_work.h>
#include <nds.h>
#include <platform_defines.h>
#include <assets/ui/GFX_ui.h>

void NDS_set_ui_container_to__work(
        UI_Element *p_ui_container) {

}

void NDS_set_ui_background_to__work(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(GFX_uiTiles, 
            p_gfx_context->background_ui
            .gfx_tileset, GFX_uiTilesLen);
	dmaCopy(GFX_uiTiles, 
            p_gfx_context->background_ui__overlay
            .gfx_tileset, GFX_uiTilesLen);
	dmaCopy(ui_map_workMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_workMapLen);
	dmaCopy(ui_map_workMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_workMapLen);
}