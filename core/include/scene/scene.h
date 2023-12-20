#ifndef SCENE_H
#define SCENE_H

#include <defines.h>

typedef struct Scene_t {
    m_load_scene    load_handler;
    m_update_scene  update_handler;
    m_render_scene  render_handler;
    m_unload_scene  unload_handler;
} Scene;

///
/// This sets all handlers to nullptr.
/// 
void init_scene(Scene* scene);

#endif
