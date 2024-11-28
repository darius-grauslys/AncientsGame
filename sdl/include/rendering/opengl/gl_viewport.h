#ifndef GL_VIEWPORT_H
#define GL_VIEWPORT_H

#include "gl_defines.h"

void GL_initialize_viewport_stack(
        GL_Viewport_Stack *p_GL_viewport_stack,
        GLint x__initial,
        GLint y__initial,
        GLint width__initial,
        GLint height__initial);

void GL_push_viewport(
        GL_Viewport_Stack *p_GL_viewport,
        GLint x,
        GLint y,
        GLint width,
        GLint height);

void GL_pop_viewport(
        GL_Viewport_Stack *p_GL_viewport);

void GL_refresh_viewport_on_top_of__viewport_stack(
        GL_Viewport_Stack *p_GL_viewport_stack);

static inline
bool GL_is_viewport_stack_on__initial_viewport(
        GL_Viewport_Stack *p_GL_viewport_stack) {
    return p_GL_viewport_stack
        ->p_GL_viewport__current
        == &p_GL_viewport_stack
        ->GL_viewport_stack[0]
        ;
}

static inline
bool GL_is_viewport_stack__full(
        GL_Viewport_Stack *p_GL_viewport_stack) {
    return p_GL_viewport_stack
        ->p_GL_viewport__current
        - p_GL_viewport_stack
        ->GL_viewport_stack
        >= (MAX_QUANTITY_OF__VIEWPORTS-1)
        ;
}

static inline
bool GL_is_viewport_stack__only_the_base(
        GL_Viewport_Stack *p_GL_viewport_stack) {
    return p_GL_viewport_stack
        ->p_GL_viewport__current
        == p_GL_viewport_stack
        ->p_GL_viewport__base
        ;
}

static inline
GL_Viewport *GL_peek_viewport_stack(
        GL_Viewport_Stack *p_GL_viewport) {
    return p_GL_viewport->p_GL_viewport__current;
}

#endif
