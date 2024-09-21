#include <rendering/opengl/gl_shader_passthrough.h>

const char *_source_shader_passthrough__vertex = "\n\
#version 330 core\n\
layout(location = 0) in vec3 position;\n\
layout(location = 1) in vec2 uv;\n\
\n\
out vec2 TexCoord;\n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(position, 1);\n\
    TexCoord = uv;\n\
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
    initialize_shader_2d(shader, _source_shader_passthrough__vertex,
            _source_shader_passthrough__fragment);
}

void render_with__shader_passthrough(
        GL_Shader_2D_Passthrough *shader,
        PLATFORM_Texture *texture_source,
        GL_Vertex_Object *vertex_object
        ) {
    use_shader_2d(shader);
    use_vertex_object(vertex_object);
    PLATFORM_use_texture(texture_source);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
