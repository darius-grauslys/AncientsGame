#include "debug/debug.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_numerics.h"
#include "vectors.h"
#include <cglm/affine.h>
#include <cglm/clipspace/ortho_lh_no.h>
#include <cglm/mat4.h>
#include <world/opengl/gl_camera.h>
#include <defines.h>

void GL_initialize_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    p_camera->position = VECTOR__3i32F4__0_0_0;
    GL_Camera_Data *p_GL_camera_data =
        p_camera->p_camera_data;

    GL_fit_projection_of__camera_to__window(
            p_PLATFORM_gfx_context,
            p_camera);

    glm_mat4_identity(
            p_GL_camera_data
            ->gl_scale__matrix_4_4);

    glm_mat4_identity(
            p_GL_camera_data
            ->gl_translation__matrix_4_4);
}

void GL_fit_projection_of__camera_to__window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    GL_Camera_Data *p_GL_camera_data =
        p_camera->p_camera_data;

    float width = 16;
    float height = 12;

    // TODO: magic numbers
    glm_ortho_lh_no(
            -width, width,
            -height, height,
            -0.1, 
             100, 
            p_GL_camera_data
            ->gl_projection__matrix_4_4);
}

void GL_update_camera(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Camera *p_camera) {
    if (!p_camera->p_camera_data) {
        debug_error("SDL::GL::GL_update_camera, p_camera_data == 0.");
        return;
    }

    GL_Camera_Data *p_GL_camera_data =
        (GL_Camera_Data*)p_camera->p_camera_data;

    vec3 vector_xyz;
    vector_3i32F4_to__vec3(
            p_camera->position, 
            vector_xyz);

    glm_translate_make(
            p_GL_camera_data->gl_translation__matrix_4_4, 
            vector_xyz);
}

