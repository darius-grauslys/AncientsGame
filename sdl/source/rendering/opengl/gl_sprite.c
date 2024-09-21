#include "defines_weak.h"
#include "rendering/opengl/gl_shader_sprite.h"
#include "rendering/opengl/gl_vertex_object.h"
#include <rendering/opengl/gl_sprite.h>
#include <sdl_defines.h>

void f_GL_initialize_sprite_wrapper(
        Sprite_Wrapper *p_sprite_wrapper) {
    //TODO: impl
    debug_abort("SDL::GL::f_GL_initialize_sprite_wrapper impl");
}

void GL_initialize_sprite(
        GL_Sprite *p_GL_sprite,
        GL_Shader_2D *p_GL_shader,
        PLATFORM_Texture *p_PLATFORM_texture) {
    initialize_vertex_object_as__unit_square(
            &p_GL_sprite->GL_vertex_object);

    p_GL_sprite->location_of__sprite_frame_row_col
        = glGetUniformLocation(p_GL_sprite->p_GL_shader->handle, 
                "spriteframe_row_col");
    p_GL_sprite->location_of__sprite_frame_width_height
        = glGetUniformLocation(p_GL_sprite->p_GL_shader->handle, 
                "spriteframe_width_height");
}

void GL_release_sprite(
        GL_Sprite *p_GL_sprite) {
    release_vertex_object(
            &p_GL_sprite->GL_vertex_object);
}
