#include <ui/menu/nds_ui__menu__multiplayer.h>
#include <assets/ui/default/ui_map_multiplayer.h>
#include <nds.h>
#include <platform_defines.h>

void NDS_set_ui_manager_to__multiplayer(
        UI_Manager *p_ui_manager) {

}

void NDS_set_ui_background_to__menu_multiplayer(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_multiplayerMap, 
            p_gfx_context->backgrounds__sub[0]
            .gfx_map,
            ui_map_multiplayerMapLen);
	dmaCopy(ui_map_multiplayerMap, 
            p_gfx_context->backgrounds__sub[1]
            .gfx_map,
            ui_map_multiplayerMapLen);
}
