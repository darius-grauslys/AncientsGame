#include <ui/menu/nds_ui__menu__singleplayer.h>
#include <assets/ui/ui_map_singleplayer.h>
#include <nds.h>
#include <platform_defines.h>

void NDS_set_ui_manager_to__singleplayer(
        UI_Manager *p_ui_manager);

void NDS_set_ui_background_to__menu_single_player(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_singleplayerMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_singleplayerMapLen);
	dmaCopy(ui_map_singleplayerMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_singleplayerMapLen);
}