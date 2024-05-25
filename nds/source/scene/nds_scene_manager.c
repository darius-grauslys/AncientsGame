#include "scene/scene__game.h"
#include "scene/scene__main_menu.h"
#include "scene/scene__multiplayer_menu.h"
#include "scene/scene__settings_menu.h"
#include "scene/scene__single_player_menu.h"
#include "scene/scene_manager.h"
#include <platform.h>

void PLATFORM_establish_scenes(Scene_Manager *p_scene_manager) {
    p_scene_manager->p_active_scene =
        get_scene_ptr_from__scene_manager(
                p_scene_manager, 
                SCENE_IDENTIFIER__MAIN_MENU);

    init_scene_as__main_menu(
            get_scene_ptr_from__scene_manager(
                p_scene_manager, 
                SCENE_IDENTIFIER__MAIN_MENU));
    init_scene_as__single_player_menu(
            get_scene_ptr_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__SINGLE_PLAYER_MENU));
    init_scene_as__multiplayer_menu(
            get_scene_ptr_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__MULTIPLAYER_MENU));
    init_scene_as__settings_menu(
            get_scene_ptr_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__SETTINGS_MENU));
    init_scene_as__game(
            get_scene_ptr_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__GAME));
}
