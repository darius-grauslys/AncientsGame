#include <nds.h>

#include <ui/nds_ui.h>

#include <assets/ui/_ui_tiles.h>
#include <assets/ui/ui_map_equip.h>
#include <assets/ui/ui_map_ground.h>
#include <assets/ui/ui_map_work.h>
#include <assets/ui/ui_map_main_menu.h>
#include <assets/ui/ui_map_singleplayer.h>
#include <assets/ui/ui_map_multiplayer.h>
#include <assets/ui/ui_map_settings.h>

void NDS_set_ui_to__debug(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(_ui_tilesMap, 
            p_gfx_context->background_ui
            .gfx_map,
            _ui_tilesMapLen);
	dmaCopy(_ui_tilesMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            _ui_tilesMapLen);
}
void NDS_set_ui_to__equip(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_equipMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_equipMapLen);
	dmaCopy(ui_map_equipMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_equipMapLen);
}
void NDS_set_ui_to__ground(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_groundMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_groundMapLen);
	dmaCopy(ui_map_groundMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_groundMapLen);
}
void NDS_set_ui_to__work(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_workMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_workMapLen);
	dmaCopy(ui_map_workMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_workMapLen);
}

void NDS_set_ui_to__menu_main(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_main_menuMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_main_menuMapLen);
	dmaCopy(ui_map_main_menuMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_main_menuMapLen);
}
void NDS_set_ui_to__menu_single_player(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_singleplayerMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_singleplayerMapLen);
	dmaCopy(ui_map_singleplayerMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_singleplayerMapLen);
}
void NDS_set_ui_to__menu_multiplayer(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_multiplayerMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_multiplayerMapLen);
	dmaCopy(ui_map_multiplayerMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_multiplayerMapLen);
}
void NDS_set_ui_to__menu_settings(PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_settingsMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_settingsMapLen);
	dmaCopy(ui_map_settingsMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_settingsMapLen);
}
