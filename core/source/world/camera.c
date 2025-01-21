#include "numerics.h"
#include "vectors.h"
#include <world/camera.h>

void m_camera_handler__default(
        Camera *p_this_camera,
        Game *p_game) {
    Entity *p_local_player =
        p_game->world.entity_manager.p_local_player;
    if (!p_local_player) {
        return;
    }
    set_position_of__camera_to__entity(
            p_this_camera, 
            p_local_player);
}

void initialize_camera(
        Camera *p_camera,
        Vector__3i32F4 position,
        m_Camera_Handler m_camera_handler,
        Quantity__u32 width_of__fulcrum,
        Quantity__u32 height_of__fulcrum,
        i32F20 z_near,
        i32F20 z_far) {
    p_camera->position = 
        position;
    p_camera->m_camera_handler =
        (m_camera_handler)
        ? m_camera_handler
        : m_camera_handler__default
        ;
    p_camera->height_of__fulcrum =
        height_of__fulcrum;
    p_camera->width_of__fulcrum =
        width_of__fulcrum;
    p_camera->z_near = z_near;
    p_camera->z_far = z_far;
}

bool is_camera__active(
        Camera *p_camera) {
    return 
        p_camera->m_camera_handler
        && !is_quantity_u32__out_of_bounds(
                p_camera->height_of__fulcrum)
        && !is_quantity_u32__out_of_bounds(
                p_camera->width_of__fulcrum)
        && !is_vectors_3i32F4__out_of_bounds(
                p_camera->position)
        && (p_camera->z_near < p_camera->z_far);
}
