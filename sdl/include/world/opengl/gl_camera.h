#ifndef GL_CAMERA_H
#define GL_CAMERA_H

#include "defines_weak.h"
#include "rendering/opengl/gl_defines.h"
#include <sdl_defines.h>

void GL_initialize_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

void GL_fit_projection_of__camera_to__window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

void GL_update_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

static inline
bool GL_is_camera_data__allocated(
        GL_Camera_Data *p_GL_camera_data) {
    return p_GL_camera_data->is_allocated;
}

static inline
void GL_set_camera_data_as__allocated(
        GL_Camera_Data *p_GL_camera_data) {
    p_GL_camera_data->is_allocated = true;
}

static inline
void GL_set_camera_data_as__deallocated(
        GL_Camera_Data *p_GL_camera_data) {
    p_GL_camera_data->is_allocated = false;
}

#endif
