#include "scene/scene_manager.h"
#include <scene/sdl_scene_manager.h>
#include <scene/sdl_scene__test.h>

void SDL_establish_scenes(Scene_Manager *p_scene_manager) {
    
    p_scene_manager->p_active_scene =
        get_p_scene_from__scene_manager(
                p_scene_manager, 
                SCENE_IDENTIFIER__TEST);

    initialize_scene_as__test(
            get_p_scene_from__scene_manager(
				p_scene_manager,
				SCENE_IDENTIFIER__TEST));
}
