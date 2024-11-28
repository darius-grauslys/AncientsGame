#include "rendering/opengl/gl_render_world.h"
#include "game.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_viewport.h"
#include "rendering/sdl_render_world.h"

void GL_render_world(Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    GL_Viewport_Stack *p_GL_viewport_stack =
        GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                p_PLATFORM_gfx_context);

    i32 width  = p_PLATFORM_gfx_context->width_of__sdl_window;
    i32 height = p_PLATFORM_gfx_context->height_of__sdl_window;

    i32 minima = (width > height)
        ? height
        : width
        ;

    i32 width__fixed = minima / 32;
    i32 height__fixed = width__fixed * 28 / 32;

    width__fixed *= 32;
    height__fixed *= 32;

    GL_push_viewport(
            p_GL_viewport_stack, 
            (width - width__fixed) / 2,
            (height - width__fixed) / 2,
            width__fixed,
            height__fixed);

    f_SDL_render_world__default(p_game);

    GL_pop_viewport(
            p_GL_viewport_stack);
}
