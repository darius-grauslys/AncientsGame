#include "world/camera.h"
#include "world/world.h"
#include <entity/handlers/entity_handlers.h>
#include <game.h>
#include <debug/debug.h>

void m_entity_dispose_handler__default(
        Entity *p_this_entity,
        Game *p_game) {
        debug_info("release_entity_from__world: %p",
                p_this_entity);
}

void m_camera_handler_for__entity_tracking(
        Camera *p_this_camera,
        Game *p_game) {
    if (!p_this_camera->p_camera_data) {
        return;
    }
    Entity *p_entity_to__track =
        (Entity*)p_this_camera->p_camera_data;
    set_position_of__camera_to__entity(
            p_this_camera, 
            p_entity_to__track);
}
