#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <defines.h>

void initialize_scene_manager(
        Scene_Manager *p_scene_manager);

static Scene inline *get_p_active_scene_from__scene_manager(
        Scene_Manager *p_scene_manager) {
    return p_scene_manager->p_active_scene;
}

static Scene inline *get_p_scene_from__scene_manager(
        Scene_Manager *p_scene_manager,
        Identifier__u16 identifier) {
#ifndef NDEBUG
    if (identifier >= SCENE_MAX_QUANTITY_OF) {
        debug_abort("get_scene_ptr_from__scene_manager, Scene Identifier %d invalid.", 
                identifier);
        return 0;
    }
#endif
    return &p_scene_manager->scenes[identifier];
}

static void inline set_p_active_scene_for__scene_manager(
        Scene_Manager *p_scene_manager,
        Identifier__u16 identifier) {
    Scene *p_scene =
        get_p_scene_from__scene_manager(
                p_scene_manager, identifier);
    if (!p_scene_manager->p_active_scene) {
        p_scene_manager->p_active_scene->is_active = false;
    }
    p_scene_manager->p_active_scene = p_scene;
    p_scene->is_active = true;
}

#endif
