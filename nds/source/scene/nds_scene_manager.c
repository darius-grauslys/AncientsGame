#include "nds/ndstypes.h"
#include "nds/arm9/exceptions.h"
#include "platform_defines.h"
#include "scene/scene__game.h"
#include "scene/scene__main_menu.h"
#include "scene/scene__multiplayer_menu.h"
#include "scene/scene__settings_menu.h"
#include "scene/scene__single_player_menu.h"
#include "scene/scene__test.h"
#include "scene/scene_manager.h"
#include <platform.h>
#include <debug/nds_debug.h>

extern Game game;

void _abort(void) {
    game.scene_manager.p_active_scene = 0;
}

void PLATFORM_establish_scenes(Scene_Manager *p_scene_manager) {
    setExceptionHandler(_abort);

    p_scene_manager->p_active_scene =
        get_p_scene_from__scene_manager(
                p_scene_manager, 
                SCENE_IDENTIFIER__TEST);

    initialize_scene_as__main_menu(
            get_p_scene_from__scene_manager(
                p_scene_manager, 
                SCENE_IDENTIFIER__MAIN_MENU));
    initialize_scene_as__single_player_menu(
            get_p_scene_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__SINGLE_PLAYER_MENU));
    initialize_scene_as__multiplayer_menu(
            get_p_scene_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__MULTIPLAYER_MENU));
    initialize_scene_as__settings_menu(
            get_p_scene_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__SETTINGS_MENU));
    initialize_scene_as__game(
            get_p_scene_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__GAME));
    initialize_scene_as__test(
            get_p_scene_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__TEST));
}
