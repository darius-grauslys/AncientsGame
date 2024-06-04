#include <ui/game/nds_ui__equip.h>
#include <nds.h>
#include <assets/ui/ui_map_equip.h>
#include <platform_defines.h>

void NDS_set_ui_container_to__equip(
        UI_Element *p_ui_container) {

}

void NDS_set_ui_background_to__equip(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_equipMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_equipMapLen);
	dmaCopy(ui_map_equipMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_equipMapLen);
}
