#ifndef GL_SHADER_SPRITE_H
#define GL_SHADER_SPRITE_H

#include "defines_weak.h"
#include <rendering/opengl/gl_defines.h>

void initialize_shader_2d_as__shader_sprite(
        GL_Shader_2D *shader);

void m_SDL_render_sprite_with__gl(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        Sprite_Wrapper *p_sprite_wrapper);

#endif
