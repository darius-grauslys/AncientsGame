#include "rendering/opengl/gl_render_world.h"
#include "game.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_viewport.h"
#include "rendering/sdl_render_world.h"
#include "rendering/gfx_context.h"

void GL_render_world(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__gfx_context(
                p_gfx_context);

    GL_Viewport_Stack *p_GL_viewport_stack =
        GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);

    i32 width  = 
        p_gfx_window
        ->p_PLATFORM_gfx_window
        ->p_SDL_graphics_window__texture
        ->width
        ;
    i32 height =
        p_gfx_window
        ->p_PLATFORM_gfx_window
        ->p_SDL_graphics_window__texture
        ->height
        ;

    GL_push_viewport(
            p_GL_viewport_stack, 
            0,
            0,
            width,
            height);

    f_SDL_render_world__default(
            p_gfx_context,
            p_gfx_window,
            p_world);

    GL_pop_viewport(
            p_GL_viewport_stack);
}
