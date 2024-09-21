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

void m_SDL_render_sprite_with__gl(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Wrapper *p_sprite_wrapper) {

    PLATFORM_Sprite *p_PLATFORM_sprite =
        p_sprite_wrapper->p_sprite;

    u8 frame = p_sprite_wrapper->frame__current;
    u8 frame__x =
        frame 
        % p_PLATFORM_sprite->quantity_of__sprite_frame__columns;
    u8 frame__y =
        frame 
        / p_PLATFORM_sprite->quantity_of__sprite_frame__columns;

    GL_Sprite *p_GL_sprite =
        (GL_Sprite*)p_sprite_wrapper
        ->p_sprite
        ->p_SDL_sprite;
    use_shader_2d(p_GL_sprite->p_GL_shader);
#ifndef NDEBUG
    if (p_GL_sprite->location_of__sprite_frame_row_col
            == -1) {
        debug_abort("SDL::GL::m_SDL_render_sprite_with__gl, bad shader. (location_of__sprite_frame_row_col not found.)");
        return;
    }
    if (p_GL_sprite->location_of__sprite_frame_width_height
            == -1) {
        debug_abort("SDL::GL::m_SDL_render_sprite_with__gl, bad shader. (location_of__sprite_frame_width_height not found.)");
        return;
    }
#endif
    glUniform2f(
            p_GL_sprite->location_of__sprite_frame_row_col, 
            frame__x, 
            frame__y);
    glUniform2f(
            p_GL_sprite->location_of__sprite_frame_width_height, 
            p_GL_sprite->sprite_frame__width, 
            p_GL_sprite->sprite_frame__height);
    use_vertex_object(&p_GL_sprite->GL_vertex_object);
    PLATFORM_use_texture(p_GL_sprite->p_PLATFORM_texture);

    //TODO: take in camera matrices

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
