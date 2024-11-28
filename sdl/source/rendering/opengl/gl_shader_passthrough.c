#include <rendering/opengl/gl_shader_passthrough.h>

const char *_source_shader_passthrough__vertex = "\n\
#version 330 core\n\
layout(location = 0) in vec3 position;\n\
layout(location = 1) in vec2 uv;\n\
uniform vec2 uv_index;\n\
uniform vec2 uv_dimensions;\n\
uniform vec2 uv_flip;\n\
\n\
out vec2 TexCoord;\n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(position, 1);\n\
    TexCoord = vec2((uv_dimensions.x * \n\
            (abs(uv_flip.x-uv.x)) + uv_index.x),\n\
            (uv_dimensions.y * \n\
            (abs(uv_flip.y-uv.y)) + uv_index.y));\n\
}";

const char *_source_shader_passthrough__fragment = " \n\
#version 330 core\n\
uniform sampler2D _sample;\n\
\n\
in vec2 TexCoord;\n\
out vec4 color;\n\
\n\
void main()\n\
{\n\
    color = texture(_sample, TexCoord);\n\
    color.a = 1.0;\n\
    if (color.r == 1.0 && color.g == 0.0 && color.b == 1.0) {\n\
        discard;\n\
    }\n\
}";

void get_source__shader_passthrough(
        const char **source_vertex,
        const char **source_fragment) {
    *source_vertex =
        _source_shader_passthrough__vertex;
    *source_fragment =
        _source_shader_passthrough__fragment;
}

void initialize_shader_2d_as__shader_passthrough(
        GL_Shader_2D_Passthrough *shader) {
    initialize_shader_2d(
            shader, 
            _source_shader_passthrough__vertex,
            _source_shader_passthrough__fragment);

    shader->location_of__general_uniform_0 =
        glGetUniformLocation(
                shader->handle, 
                "uv_index");
    shader->location_of__general_uniform_1 =
        glGetUniformLocation(
                shader->handle, 
                "uv_dimensions");
    shader->location_of__general_uniform_2 =
        glGetUniformLocation(
                shader->handle, 
                "uv_flip");
}

void GL_render_with__shader__passthrough_using__index_sampling(
        GL_Shader_2D *p_GL_shader__passthrough,
        float x__uv,
        float y__uv,
        float width_of__uv,
        float height_of__uv,
        bool is_flipped_on__x,
        bool is_flipped_on__y) {
    glUniform2f(
            p_GL_shader__passthrough->location_of__general_uniform_0,
            x__uv * width_of__uv,
            1.0f 
            - (y__uv * height_of__uv)
            - height_of__uv
            );
    glUniform2f(
            p_GL_shader__passthrough->location_of__general_uniform_1,
            width_of__uv,
            height_of__uv);
    glUniform2f(
            p_GL_shader__passthrough->location_of__general_uniform_2,
            (is_flipped_on__x)
            ? 1.0
            : 0.0,
            (is_flipped_on__y)
            ? 1.0
            : 0.0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GL_render_with__shader__passthrough_using__coordinate_sampling(
        GL_Shader_2D *p_GL_shader__passthrough,
        float x__uv,
        float y__uv,
        float width_of__uv,
        float height_of__uv,
        bool is_flipped_on__x,
        bool is_flipped_on__y) {
    glUniform2f(
            p_GL_shader__passthrough->location_of__general_uniform_0,
            x__uv,
            1.0f 
            - y__uv
            - height_of__uv
            );
    glUniform2f(
            p_GL_shader__passthrough->location_of__general_uniform_1,
            width_of__uv,
            height_of__uv);
    glUniform2f(
            p_GL_shader__passthrough->location_of__general_uniform_2,
            (is_flipped_on__x)
            ? 1.0
            : 0.0,
            (is_flipped_on__y)
            ? 1.0
            : 0.0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
