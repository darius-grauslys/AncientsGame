#include "input/opengl/gl_input.h"
#include "game.h"
#include "numerics.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_viewport.h"

void GL_process_input(
        Game *p_game,
        Input *p_input) {
    GL_Viewport_Stack *p_GL_viewport_stack =
        GL_get_p_viewport_stack_from__PLATFORM_gfx_context(
                get_p_PLATFORM_gfx_context_from__game(p_game));
    GL_Viewport *p_GL_viewport =
        GL_get_p_viewport__base_from__viewport_stack(
                p_GL_viewport_stack);

    clamp__p_i32(
            &p_input->cursor__3i32.x__i32,
            p_GL_viewport->x, 
            p_GL_viewport->x
            + p_GL_viewport->width);
    clamp__p_i32(
            &p_input->cursor__3i32.y__i32,
            p_GL_viewport->y, 
            p_GL_viewport->y
            + p_GL_viewport->height);

    p_input->cursor__3i32.x__i32 -=
        p_GL_viewport->x;
    p_input->cursor__3i32.y__i32 -=
        p_GL_viewport->y;

    float x = (float)p_input->cursor__3i32.x__i32
        / (float)p_GL_viewport->width;
    float y = (float)p_input->cursor__3i32.y__i32
        / (float)p_GL_viewport->height;

    x *= 256.0f;
    y *= 256.0f;

    p_input->cursor__3i32.x__i32 = (i32)x;
    p_input->cursor__3i32.y__i32 = (i32)y;
}
