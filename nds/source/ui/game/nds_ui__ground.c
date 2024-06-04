#include <ui/game/nds_ui__ground.h>
#include <nds.h>
#include <platform_defines.h>
#include <assets/ui/ui_map_ground.h>

void NDS_set_ui_container_to__ground(
        UI_Element *p_ui_container) {

}

void NDS_set_ui_background_to__ground(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_groundMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_groundMapLen);
	dmaCopy(ui_map_groundMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_groundMapLen);
}
