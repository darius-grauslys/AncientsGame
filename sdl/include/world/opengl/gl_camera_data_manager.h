#ifndef GL_CAMERA_DATA_MANAGER_H
#define GL_CAMERA_DATA_MANAGER_H

#include <rendering/opengl/gl_defines.h>

void GL_initialize_camera_data_manager(
        GL_Camera_Data_Manager *p_GL_camera_data_manager);

GL_Camera_Data *GL_allocate_camera_data_with__camera_data_manager(
        GL_Camera_Data_Manager *p_GL_camera_data_manager);

void GL_release_camera_data_from__camera_data_manager(
        GL_Camera_Data_Manager *p_GL_camera_data_manager,
        GL_Camera_Data *p_GL_camera_data);

void GL_allocate_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

void GL_release_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera);

#endif
