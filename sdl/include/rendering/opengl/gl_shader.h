#ifndef SHADER_H
#define SHADER_H

#include <rendering/opengl/gl_defines.h>
#include <stdint.h>

int initialize_shader_2d(GL_Shader_2D *shader, const char *source_vertex,
        const char *source_fragment);
int use_shader_2d(GL_Shader_2D *shader);
int release_shader_2d(GL_Shader_2D *shader);

void inline set_shader_mat4_model__scale(GL_Shader_2D *shader, float scale) {
    shader->mat4_model[0][0] = scale;
    shader->mat4_model[1][1] = scale;
    shader->mat4_model[2][2] = scale;
}
void inline set_shader_mat4_model__position(GL_Shader_2D *shader,
        float x, float y, float z) {
    shader->mat4_model[0][3] = x;
    shader->mat4_model[1][3] = y;
    shader->mat4_model[2][3] = z;
}
void inline set_shader_mat4_view__scale(GL_Shader_2D *shader, float scale) {
    shader->mat4_view[0][0] = scale;
    shader->mat4_view[1][1] = scale;
    shader->mat4_view[2][2] = scale;
}
void inline set_shader_mat4_view__position(GL_Shader_2D *shader,
        float x, float y, float z) {
    shader->mat4_view[0][3] = x;
    shader->mat4_view[1][3] = y;
    shader->mat4_view[2][3] = z;
}
static void inline set_shader_mat4_projection__orthographic(
        GL_Shader_2D *shader,
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
