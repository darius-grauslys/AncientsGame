#ifndef SHADER_H
#define SHADER_H

#include <rendering/opengl/gl_defines.h>
#include <stdint.h>

///
/// Call release_shader_2d before recalling
/// any initializers otherwise you will leak GPU memory.
///

void initialize_shader_2d_as__deallocated(
        GL_Shader_2D *p_GL_shader);
int initialize_shader_2d(
        GL_Shader_2D *shader, 
        const char *source_vertex,
        const char *source_fragment);
int use_shader_2d(GL_Shader_2D *shader);
int release_shader_2d(GL_Shader_2D *shader);

void GL_link_projection_to__shader(
        GL_Shader_2D *p_GL_shader,
        float projection[16]);

void GL_link_translation_to__shader(
        GL_Shader_2D *p_GL_shader,
        Vector__3i32F4 translation);

void GL_link_camera_projection_to__shader(
        GL_Shader_2D *p_GL_shader,
        Camera *p_camera);

void GL_link_camera_translation_to__shader(
        GL_Shader_2D *p_GL_shader,
        Camera *p_camera);

void GL_link_model_data_to__shader(
        GL_Shader_2D *p_GL_shader,
        Vector__3i32F4 position,
        i32F4 scale);

void GL_link_data_to__shader(
        GL_Shader_2D *p_GL_shader,
        Camera *p_camera,
        Vector__3i32F4 position__3i32F4,
        i32F4 scale);

static inline
bool GL_is_shader__allocated(
        GL_Shader_2D *p_GL_shader) {
    return p_GL_shader->is_shader__allocated;
}

static inline
void GL_set_shader_as__allocated(
        GL_Shader_2D *p_GL_shader) {
    p_GL_shader->is_shader__allocated = true;
}

static inline
void GL_set_shader_as__deallocated(
        GL_Shader_2D *p_GL_shader) {
    p_GL_shader->is_shader__allocated = false;
}

static inline
bool GL_does_shader_utilize__projection_mat_4_4(
        GL_Shader_2D *p_GL_shader) {
    return p_GL_shader->location_of__projection_mat_4_4 != -1;
}

static inline
bool GL_does_shader_utilize__translation_mat_4_4(
        GL_Shader_2D *p_GL_shader) {
    return p_GL_shader->location_of__translation_mat_4_4 != -1;
}

static inline
bool GL_does_shader_utilize__model_mat_4_4(
        GL_Shader_2D *p_GL_shader) {
    return p_GL_shader->location_of__model_mat_4_4 != -1;
}

#endif 
