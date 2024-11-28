#include "rendering/opengl/gl_defines.h"
#include <rendering/opengl/gl_viewport.h>

void GL_initialize_viewport_stack(
        GL_Viewport_Stack *p_GL_viewport_stack,
        GLint x__initial,
        GLint y__initial,
        GLint width__initial,
        GLint height__initial) {
    p_GL_viewport_stack->p_GL_viewport__current =
        &p_GL_viewport_stack->GL_viewport_stack[0];
    p_GL_viewport_stack->p_GL_viewport__base =
        &p_GL_viewport_stack->GL_viewport_stack[0];

    p_GL_viewport_stack
        ->p_GL_viewport__current->x = x__initial;
    p_GL_viewport_stack
        ->p_GL_viewport__current->y = y__initial;
    p_GL_viewport_stack
        ->p_GL_viewport__current->width = width__initial;
    p_GL_viewport_stack
        ->p_GL_viewport__current->height = height__initial;

    glViewport(
            x__initial, 
            y__initial, 
            width__initial, 
            height__initial);
}

static inline
bool GL_DEBUG_verify_viewport_stack_integrity(
        GL_Viewport_Stack *p_GL_viewport_stack,
        GL_Viewport *p_GL_viewport__current,
        const char *p_c_str_of__callee) {
#ifndef NDEBUG
    int index =
        p_GL_viewport__current
        - p_GL_viewport_stack
        ->GL_viewport_stack
        ;
    if (index < 0
            || index >= MAX_QUANTITY_OF__VIEWPORTS) {
        debug_warning("Do not modify the internals of GL_Viewport_Stack!");
        debug_abort("%s, viewport integrity compromised.");
        return true;
    }
#endif
    return false;
}

void GL_push_viewport(
        GL_Viewport_Stack *p_GL_viewport_stack,
        GLint x,
        GLint y,
        GLint width,
        GLint height) {
    if (GL_is_viewport_stack__full(
                p_GL_viewport_stack)) {
        debug_warning("Modify MAX_QUANTITY_OF__VIEWPORTS if needed.");
        debug_error("SDL::GL::GL_push_viewport, viewport stack is full.");
    }

    GL_Viewport **p_GL_viewport__current =
        &p_GL_viewport_stack
        ->p_GL_viewport__current;

    (*p_GL_viewport__current)++;

    if (GL_DEBUG_verify_viewport_stack_integrity(
                p_GL_viewport_stack, 
                *p_GL_viewport__current, 
                "SDL::GL::GL_push_viewport")) {
        return;
    }

    (*p_GL_viewport__current)->x = x;
    (*p_GL_viewport__current)->y = y;
    (*p_GL_viewport__current)->width = width;
    (*p_GL_viewport__current)->height = height;

    glViewport(x, y, width, height);
}

void GL_pop_viewport(
        GL_Viewport_Stack *p_GL_viewport_stack) {
    if (GL_is_viewport_stack_on__initial_viewport(
                p_GL_viewport_stack)) {
        debug_warning("Instead, use GL_initialize_viewport_stack.");
        debug_error("SDL::GL::GL_pop_viewport, cannot pop the last viewport from the viewport stack.");
    }

    GL_Viewport **p_GL_viewport__current =
        &p_GL_viewport_stack
        ->p_GL_viewport__current;

    (*p_GL_viewport__current)--;

    if (GL_DEBUG_verify_viewport_stack_integrity(
                p_GL_viewport_stack, 
                *p_GL_viewport__current, 
                "SDL::GL::GL_pop_viewport")) {
        return;
    }

    glViewport(
            (*p_GL_viewport__current)->x, 
            (*p_GL_viewport__current)->y, 
            (*p_GL_viewport__current)->width, 
            (*p_GL_viewport__current)->height);
}

void GL_refresh_viewport_on_top_of__viewport_stack(
        GL_Viewport_Stack *p_GL_viewport_stack) {

    GL_Viewport **p_GL_viewport__current =
        &p_GL_viewport_stack
        ->p_GL_viewport__current;

    glViewport(
            (*p_GL_viewport__current)->x, 
            (*p_GL_viewport__current)->y, 
            (*p_GL_viewport__current)->width, 
            (*p_GL_viewport__current)->height);
}
