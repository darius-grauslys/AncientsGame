#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <defines.h>

void initialize_scene_manager(
        Scene_Manager *p_scene_manager);

Scene *get_p_scene_from__scene_manager(
        Scene_Manager *p_scene_manager,
        Identifier__u16 identifier);

void set_p_active_scene_for__scene_manager(
        Scene_Manager *p_scene_manager,
        Identifier__u16 identifier);

void quit_scene_state_machine(Scene_Manager *p_scene_manager);

static inline 
Scene *get_p_active_scene_from__scene_manager(
        Scene_Manager *p_scene_manager) {
    return p_scene_manager->p_active_scene;
}

#endif
