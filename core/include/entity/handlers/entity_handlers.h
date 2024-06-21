#ifndef ENTITY_HANDLERS_H
#define ENTITY_HANDLERS_H

#include <defines.h>

void m_entity_dispose_handler__default(
        Entity *this_entity,
        Game *game);

void m_camera_handler_for__entity_tracking(
        Camera *p_this_camera,
        Game *p_game);

static inline
void set_camera_to__track_this__entity(
        Camera *p_camera,
        Entity *p_entity) {
    p_camera->m_camera_handler =
        m_camera_handler_for__entity_tracking;
    p_camera->p_camera_data =
        p_entity;
}

#endif
