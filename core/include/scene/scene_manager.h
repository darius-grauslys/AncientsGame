#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <defines.h>

void init_scene_manager(
        Scene_Manager *p_scene_manager);

static Scene inline *get_active_scene_ptr_from__scene_manager(
        Scene_Manager *p_scene_manager) {
    return p_scene_manager->p_active_scene;
}

static Scene inline *get_scene_ptr_from__scene_manager(
        Scene_Manager *p_scene_manager,
        Identifier__u16 identifier) {
#ifndef NDEBUG
    if (identifier >= SCENE_MAX_QUANTITY_OF) {
        debug_abort("Scene Identifier %d invalid, get_scene_ptr_from__scene_manager", identifier);
        return &p_scene_manager->scenes[0];
    }
    if (!p_scene_manager->scenes[identifier].is_active) {
        debug_error("Associated Scene for identifier: %d, is not active.");
    }
#endif
    return &p_scene_manager->scenes[identifier];
}

#endif