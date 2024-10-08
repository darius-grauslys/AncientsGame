#include "rendering/opengl/gl_numerics.h"
#include "rendering/opengl/glad/glad.h"
#include "sdl_numerics.h"
#include <cglm/mat4.h>
#include <rendering/opengl/gl_shader.h>
#include <debug/debug.h>
#include <stddef.h>
#include <cglm/affine.h>

void initialize_shader_2d_as__deallocated(
        GL_Shader_2D *p_GL_shader) {
    p_GL_shader->location_of__projection_mat_4_4 = -1;
    p_GL_shader->location_of__translation_mat_4_4 = -1;
    p_GL_shader->location_of__model_mat_4_4 = -1;
    p_GL_shader->is_shader__allocated = false;
}
int initialize_shader_2d(GL_Shader_2D *shader, const char *source_vertex,
        const char *source_fragment) {
    shader->handle = 0;
    shader->vertex_handle = 0;
    shader->fragment_handle = 0;

    debug_info("compiling vertex shader...");
    shader->vertex_handle = 
        glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vertex_handle, 1, &source_vertex, NULL);
    glCompileShader(shader->vertex_handle);

    glGetShaderiv(shader->vertex_handle, GL_COMPILE_STATUS,
            &shader->success_code);
    if (!shader->success_code) {
        char log[512];
        glGetShaderInfoLog(shader->vertex_handle, 512, NULL, log);
        debug_error("Failed to load vertex shader: %s", log);
        glDeleteShader(shader->vertex_handle);
        return shader->success_code;
    }

    debug_info("compiling fragment shader...");
    shader->fragment_handle = 
        glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fragment_handle, 1, &source_fragment, NULL);
    glCompileShader(shader->fragment_handle);

    glGetShaderiv(shader->fragment_handle, GL_COMPILE_STATUS,
            &shader->success_code);
    if (!shader->success_code) {
        char log[512];
        glGetShaderInfoLog(shader->fragment_handle, 512, NULL, log);
        debug_error("Failed to load fragment shader: %s", log);
        glDeleteShader(shader->vertex_handle);
        glDeleteShader(shader->fragment_handle);
        return shader->success_code;
    }

    debug_info("linking program...");
    shader->handle = glCreateProgram();
    glAttachShader(shader->handle, shader->vertex_handle);
    glAttachShader(shader->handle, shader->fragment_handle);
    glLinkProgram(shader->handle);

    glGetProgramiv(shader->handle, GL_LINK_STATUS, &shader->success_code);
    if(!shader->success_code) {
        char log[512];
        glGetProgramInfoLog(shader->fragment_handle, 512, NULL, log);
        debug_error("Failed to link shader: %s", log);
        glDeleteShader(shader->vertex_handle);
        glDeleteShader(shader->fragment_handle);
        return shader->success_code;
    }

    shader->location_of__projection_mat_4_4
        = glGetUniformLocation(
                shader->handle, 
                "projection");
    shader->location_of__translation_mat_4_4
        = glGetUniformLocation(
                shader->handle, 
                "translation");
    shader->location_of__model_mat_4_4
        = glGetUniformLocation(
                shader->handle, 
                "model");

    shader->location_of__general_uniform_0 = -1;
    shader->location_of__general_uniform_1 = -1;
    shader->location_of__general_uniform_2 = -1;
    shader->location_of__general_uniform_3 = -1;

    glDeleteShader(shader->vertex_handle);
    glDeleteShader(shader->fragment_handle);
    return 0;
}

int use_shader_2d(GL_Shader_2D *shader) {
    glUseProgram(shader->handle);
    return 0;
}

int release_shader_2d(GL_Shader_2D *shader) {
    if (!shader->handle) return 1;
    glDeleteProgram(shader->handle);
    shader->handle = 0;
    return 0;
}

void GL_link_camera_projection_to__shader(
        GL_Shader_2D *p_GL_shader,
        GL_Camera_Data *p_GL_camera_data) {
    glUniformMatrix4fv(
            p_GL_shader->location_of__projection_mat_4_4,
            1,
            false,
            (const GLfloat*)p_GL_camera_data
                ->gl_projection__matrix_4_4);
}

void GL_link_camera_translation_to__shader(
        GL_Shader_2D *p_GL_shader,
        GL_Camera_Data *p_GL_camera_data) {
    glUniformMatrix4fv(
            p_GL_shader->location_of__translation_mat_4_4,
            1,
            false,
            (const GLfloat*)p_GL_camera_data
                ->gl_translation__matrix_4_4);
}

void GL_link_model_data_to__shader(
        GL_Shader_2D *p_GL_shader,
        Vector__3i32F4 position,
        i32F4 scale) {
    mat4 model;
    glm_mat4_identity(model);
    float scale__float = i32F4_to__float(scale);
    vec3 vector3_cglm;
    vector_3i32F4_to__vec3(
            position, 
            vector3_cglm);
    glm_translate(
            model, 
            vector3_cglm);
    glm_scale_uni(model, scale__float);
    glUniformMatrix4fv(
            p_GL_shader->location_of__model_mat_4_4,
            1,
            false,
            (const GLfloat*)model);
}
