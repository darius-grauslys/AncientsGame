#ifndef SHADER_H
#define SHADER_H

#include <stdint.h>
#include <cglm/mat4.h>
#include <cglm/clipspace/ortho_rh_zo.h>

typedef struct Shader_2D_t {
    uint32_t handle;

    uint32_t vertex_handle;
    uint32_t fragment_handle;

    mat4 mat4_projection, mat4_view, mat4_model;

    uint32_t success_code;
} Shader_2D;

int initialize_shader_2d(Shader_2D *shader, const char *source_vertex,
        const char *source_fragment);
int use_shader_2d(Shader_2D *shader);
int release_shader_2d(Shader_2D *shader);

void inline set_shader_mat4_model__scale(Shader_2D *shader, float scale) {
    shader->mat4_model[0][0] = scale;
    shader->mat4_model[1][1] = scale;
    shader->mat4_model[2][2] = scale;
}
void inline set_shader_mat4_model__position(Shader_2D *shader,
        float x, float y, float z) {
    shader->mat4_model[0][3] = x;
    shader->mat4_model[1][3] = y;
    shader->mat4_model[2][3] = z;
}
void inline set_shader_mat4_view__scale(Shader_2D *shader, float scale) {
    shader->mat4_view[0][0] = scale;
    shader->mat4_view[1][1] = scale;
    shader->mat4_view[2][2] = scale;
}
void inline set_shader_mat4_view__position(Shader_2D *shader,
        float x, float y, float z) {
    shader->mat4_view[0][3] = x;
    shader->mat4_view[1][3] = y;
    shader->mat4_view[2][3] = z;
}
static void inline set_shader_mat4_projection__orthographic(
        Shader_2D *shader,
        float x, float y,
        float width, float height,
        float z_near, float z_far) {
    glm_ortho_rh_zo(
            x, y,
            x + width, y + height,
            z_near, z_far,
            shader->mat4_projection);
}

#endif 
