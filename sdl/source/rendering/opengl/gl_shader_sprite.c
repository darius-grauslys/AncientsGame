#include "rendering/opengl/gl_shader.h"
#include "rendering/opengl/gl_vertex_object.h"
#include <rendering/opengl/gl_shader_sprite.h>
#include <sdl_defines.h>

const char *_source_shader_sprite__vertex = "\n\
#version 330 core\n\
layout(location = 0) in vec3 position;\n\
layout(location = 1) in vec2 uv;\n\
uniform vec2 spriteframe_row_col;\n\
uniform vec2 spriteframe_width_height;\n\
\n\
out vec2 TexCoord;\n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(position, 1);\n\
    TexCoord = vec2(spriteframe_width_height.x * \n\
            (uv.x + spriteframe_row_col.x),\n\
            spriteframe_width_height.y * \n\
            (uv.y + spriteframe_row_col.y));\n\
}";

const char *_source_shader_sprite__fragment = " \n\
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

void initialize_shader_2d_as__shader_sprite(
        GL_Shader_2D *shader) {
    initialize_shader_2d(
            shader, 
            _source_shader_sprite__vertex,
            _source_shader_sprite__fragment);
}
