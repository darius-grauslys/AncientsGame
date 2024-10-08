#include "rendering/opengl/gl_shader.h"
#include <rendering/opengl/gl_shader_chunk.h>

const char *_source_shader_chunk__vertex = "\n\
#version 330 core\n\
layout(location = 0) in vec3 position;\n\
layout(location = 1) in vec2 uv;\n\
uniform mat4 projection;\n\
uniform mat4 translation;\n\
uniform mat4 model;\n\
\n\
out vec2 TexCoord;\n\
\n\
void main()\n\
{\n\
    gl_Position = (projection * translation * model) * (vec4(position, 1));\n\
    TexCoord = uv;\n\
}";

const char *_source_shader_chunk__fragment = " \n\
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

void initialize_shader_2d_as__shader_chunk(
        GL_Shader_2D *p_GL_shader) {
    initialize_shader_2d(
            p_GL_shader, 
            _source_shader_chunk__vertex,
            _source_shader_chunk__fragment);
}

