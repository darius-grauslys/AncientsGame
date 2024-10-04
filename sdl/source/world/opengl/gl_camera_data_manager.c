#include "defines_weak.h"
#include "rendering/opengl/gl_defines.h"
#include "world/opengl/gl_camera.h"
#include <world/opengl/gl_camera_data_manager.h>

void GL_initialize_camera_data_manager(
        GL_Camera_Data_Manager *p_GL_camera_data_manager) {
    for (Index__u16 index_of__p_GL_camera_data = 0;
            index_of__p_GL_camera_data < MAX_QUANTITY_OF__GL_CAMERA_DATA;
            index_of__p_GL_camera_data++) {
        GL_Camera_Data *p_GL_camera_data =
            &p_GL_camera_data_manager
            ->gl_camera_datas[index_of__p_GL_camera_data]
            ;
        GL_set_camera_data_as__deallocated(
                p_GL_camera_data);
    }
}

GL_Camera_Data *GL_allocate_camera_data_with__camera_data_manager(
        GL_Camera_Data_Manager *p_GL_camera_data_manager) {
    for (Index__u16 index_of__p_GL_camera_data = 0;
            index_of__p_GL_camera_data < MAX_QUANTITY_OF__GL_CAMERA_DATA;
            index_of__p_GL_camera_data++) {
        GL_Camera_Data *p_GL_camera_data =
            &p_GL_camera_data_manager
            ->gl_camera_datas[index_of__p_GL_camera_data]
            ;
        if (GL_is_camera_data__allocated(
                    p_GL_camera_data))
            continue;

        GL_set_camera_data_as__allocated(
                p_GL_camera_data);

        return p_GL_camera_data;
    }
    return 0;
}

void GL_release_camera_data_from__camera_data_manager(
        GL_Camera_Data_Manager *p_GL_camera_data_manager,
        GL_Camera_Data *p_GL_camera_data) {
    int index = 
        p_GL_camera_data
            - p_GL_camera_data_manager->gl_camera_datas
            ;
    if (index < 0
            || index >= MAX_QUANTITY_OF__GL_CAMERA_DATA) {
        debug_error("SDL::GL::GL_release_camera_data_from__camera_data_manager, p_GL_camera_data was not allocated with given manager.");
        return;
    }

    GL_set_camera_data_as__deallocated(
            p_GL_camera_data);
}

void GL_allocate_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    if (p_camera->p_camera_data) {
        debug_warning__verbose("SDL::GL::GL_allocate_camera_data, p_camera_data != 0. Leaking?");
    }

    GL_Camera_Data *p_GL_camera_data =
        GL_allocate_camera_data_with__camera_data_manager(
                GL_get_p_camera_data_manager_from__PLATFORM_gfx_context(
                    p_PLATFORM_gfx_context));

    if (!p_GL_camera_data) {
        debug_error("SDL::GL::GL_allocate_camera_data, p_GL_camera_data == 0.");
        return;
    }

    p_camera->p_camera_data =
        p_GL_camera_data
        ;
}

void GL_release_camera_data(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    if (!p_camera->p_camera_data) {
        debug_error("SDL::GL::GL_release_camera_data, p_camera_data == 0.");
        return;
    }

    GL_release_camera_data_from__camera_data_manager(
            GL_get_p_camera_data_manager_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context), 
            (GL_Camera_Data*)p_camera->p_camera_data);
}
