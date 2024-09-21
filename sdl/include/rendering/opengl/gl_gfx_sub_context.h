#ifndef GL_GFX_SUB_CONTEXT_H
#define GL_GFX_SUB_CONTEXT_H

#include "defines_weak.h"
#include "rendering/opengl/gl_defines.h"

void GL_initialize_gfx_sub_context(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Gfx_Sub_Context *p_GL_gfx_sub_context);

void GL_dispose_gfx_sub_context(
        GL_Gfx_Sub_Context *p_GL_gfx_sub_context);

void GL_clear_screen(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context);

#endif
