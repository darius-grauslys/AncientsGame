#ifndef GL_GFX_WINDOW_H
#define GL_GFX_WINDOW_H

#include "defines_weak.h"
#include "rendering/opengl/gl_defines.h"

void GL_allocate_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

void GL_render_gfx_window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window);

void GL_release_gfx_window(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window);

#endif
