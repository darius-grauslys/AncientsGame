#include "debug/debug.h"
#include "defines_weak.h"
#include "platform_defines.h"
#include <scene/scene.h>
#include <scene/scene_manager.h>

void initialize_scene_manager(
        Scene_Manager *p_scene_manager) {
    p_scene_manager->p_active_scene = 0;
    for (Quantity__u8 scene_index=0;
            scene_index<SCENE_MAX_QUANTITY_OF;
            scene_index++) {
        initialize_scene(
                get_p_scene_from__scene_manager(
                    p_scene_manager, 
                    scene_index)
                );
    }
}

Scene *get_p_scene_from__scene_manager(
        Scene_Manager *p_scene_manager,
        Identifier__u16 identifier) {
#ifndef NDEBUG
    if (identifier >= SCENE_MAX_QUANTITY_OF) {
        debug_warning("get_scene_ptr_from__scene_manager, Scene Identifier %d invalid.", 
                identifier);
        return 0;
    }
#endif
    return &p_scene_manager->scenes[identifier];
}

void set_p_active_scene_for__scene_manager(
        Scene_Manager *p_scene_manager,
        Identifier__u16 identifier) {
    Scene *p_scene =
        get_p_scene_from__scene_manager(
                p_scene_manager, identifier);
    if (!p_scene_manager->p_active_scene) {
        p_scene_manager->p_active_scene->is_active = false;
    }
    if (p_scene) {
        p_scene_manager->p_active_scene = p_scene;
        p_scene->is_active = true;
    }
}

void quit_scene_state_machine(Scene_Manager *p_scene_manager) {
    if (!p_scene_manager->p_active_scene) {
        p_scene_manager->p_active_scene->is_active = false;
    }
    p_scene_manager->p_active_scene = 0;
}
