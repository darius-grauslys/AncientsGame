#ifndef CAMERA_H
#define CAMERA_H

#include "defines_weak.h"
#include "vectors.h"
#include <defines.h>

void m_camera_handler__default(
        Camera *p_camera,
        Game *p_game);

static inline
void initialize_camera(
        Camera *p_camera,
        Vector__3i32F4 position,
        m_Camera_Handler m_camera_handler,
        Quantity__u32 width_of__fulcrum,
        Quantity__u32 height_of__fulcrum) {
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
}

static inline
void set_position_of__camera_to__entity(
        Camera *p_camera, 
        Entity *p_entity) {
    p_camera->position =
        p_entity->hitbox.position__3i32F4;
}

static inline
Vector__3i32 get_position_3i32_of__camera(
        Camera *p_camera) {
    return vector_3i32F4_to__vector_3i32(p_camera->position);
}

static inline
Vector__3i32F4 get_position_3i32F4_of__camera(
        Camera *p_camera) {
    return p_camera->position;
}

static inline
//TODO: use this in render_entity.c in NDS.
bool is_position_within__camera_fulcrum(
        Camera *p_camera,
        Vector__3i32 position) {
    Vector__3i32 camera_position__3i32 =
        get_position_3i32_of__camera(p_camera);
    //TODO: magic number the 16
    return (abs(position.x__i32 - camera_position__3i32.x__i32) 
            > p_camera->width_of__fulcrum / 2 + 16
            || abs(position.y__i32 - camera_position__3i32.y__i32) 
            > p_camera->height_of__fulcrum / 2 + 16);
}

static inline
Signed_Index__i32 get_x_i32_from__camera(
        Camera *p_camera) {
    return get_x_i32_from__vector_3i32F4(p_camera->position);
}

static inline
Signed_Index__i32 get_y_i32_from__camera(
        Camera *p_camera) {
    return get_y_i32_from__vector_3i32F4(p_camera->position);
}

static inline
Signed_Index__i32 get_z_i32_from__camera(
        Camera *p_camera) {
    return get_z_i32_from__vector_3i32F4(p_camera->position);
}

#endif
