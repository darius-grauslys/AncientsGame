#ifndef GL_SPRITE_H
#define GL_SPRITE_H

#include "defines_weak.h"
#include <rendering/opengl/gl_defines.h>

void f_GL_initialize_sprite_wrapper(
        Sprite_Wrapper *p_sprite_wrapper);

void GL_initialize_sprite(
        GL_Sprite *p_GL_sprite,
        GL_Shader_2D *p_GL_shader);

void GL_release_sprite_vertext_object(
        GL_Sprite *p_GL_sprite);

GL_Sprite *GL_get_p_sprite_from__sprite_wrapper(
        Sprite_Wrapper *p_sprite_wrapper);

GL_Sprite *GL_get_p_sprite_from__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);

void GL_render_sprite(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Wrapper *p_sprite_wrapper,
        Vector__3i32F4 position__3i32F4);

static inline
bool GL_is_sprite__allocated(
        GL_Sprite *p_GL_sprite) {
    return p_GL_sprite->is_sprite__allocated;
}

static inline
void GL_set_sprite_as__allocated(
        GL_Sprite *p_GL_sprite) {
    p_GL_sprite->is_sprite__allocated = true;
}

static inline
void GL_set_sprite_as__deallocated(
        GL_Sprite *p_GL_sprite) {
    p_GL_sprite->is_sprite__allocated = false;
}

#endif
