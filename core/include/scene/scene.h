#ifndef SCENE_H
#define SCENE_H

#include <defines.h>

void m_enter_scene_handler__default(
        Scene *p_this_scene,
        Game *p_game);

static void inline initialize_scene(Scene* scene) {
    scene->m_enter_scene_handler = m_enter_scene_handler__default;
    scene->m_load_scene_handler = 0;
    scene->m_unload_scene_handler = 0;
    scene->p_parent_scene = 0;
    scene->scene__identifier_u16 = IDENTIFIER__UNKNOWN__u16;
    scene->p_scene_data = 0;
    scene->is_active = false;
}

#endif
