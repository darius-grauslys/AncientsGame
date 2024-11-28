#ifndef SHADER_PASSTHROUGH_H
#define SHADER_PASSTHROUGH_H

#include <rendering/opengl/gl_shader.h>
#include <rendering/opengl/gl_texture.h>
#include <rendering/opengl/gl_vertex_object.h>

typedef GL_Shader_2D GL_Shader_2D_Passthrough;

void get_source__shader_passthrough(
        const char **source_vertex,
        const char **source_fragment);

void initialize_shader_2d_as__shader_passthrough(
        GL_Shader_2D_Passthrough *shader);

void GL_render_with__shader__passthrough_using__index_sampling(
        GL_Shader_2D *p_GL_shader__passthrough,
        float x__uv,
        float y__uv,
        float width_of__uv,
        float height_of__uv,
        bool is_flipped_on__x,
        bool is_flipped_on__y);

void GL_render_with__shader__passthrough_using__coordinate_sampling(
        GL_Shader_2D *p_GL_shader__passthrough,
        float x__uv,
        float y__uv,
        float width_of__uv,
        float height_of__uv,
        bool is_flipped_on__x,
        bool is_flipped_on__y);

#endif
