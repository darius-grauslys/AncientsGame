#include <ui/menu/nds_ui__menu__singleplayer.h>
#include <assets/ui/default/ui_map_singleplayer.h>
#include <nds.h>
#include <platform_defines.h>

UI_Element *NDS_allocate_ui_for__ui_window__singleplayer(
        Game *p_game) {

}

void NDS_set_ui_background_to__menu_single_player(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_singleplayerMap, 
            p_gfx_context->backgrounds__sub[0]
            .gfx_map,
            ui_map_singleplayerMapLen);
	dmaCopy(ui_map_singleplayerMap, 
            p_gfx_context->backgrounds__sub[1]
            .gfx_map,
            ui_map_singleplayerMapLen);
}
