#ifndef GL_FRAMEBUFFER_MANAGER_H
#define GL_FRAMEBUFFER_MANAGER_H

#include "sdl_defines.h"
#include <rendering/opengl/gl_defines.h>

void GL_initialize_framebuffer_manager(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager);

GL_Framebuffer *GL_allocate_framebuffer_with__framebuffer_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Framebuffer_Manager *p_GL_framebuffer_manager);

void GL_release_framebuffer_from__framebuffer_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Framebuffer_Manager *p_GL_framebuffer_manager,
        GL_Framebuffer *p_GL_framebuffer);

void GL_push_framebuffer_onto__framebuffer_manager(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager,
        GL_Framebuffer *p_GL_framebuffer);

void GL_pop_framebuffer_off_of__framebuffer_manager(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager);

GL_Framebuffer *GL_peek_framebuffer_stack_of__framebuffer_manager(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager);

void GL_use_framebuffer_thats__top_of_stack_in__framebuffer_manage(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager);

void GL_dispose_framebuffer_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Framebuffer_Manager *p_GL_framebuffer_manager);

static inline
bool GL_is_framebuffer_manager__stack__full(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager) {
    return p_GL_framebuffer_manager
        ->index_of__framebuffer_on__stack+1
        >= MAX_QUANTITY_OF__FRAMEBUFFERS
        ;
}

static inline
bool GL_is_framebuffer_manager__stack__empty(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager) {
    return p_GL_framebuffer_manager
        ->index_of__framebuffer_on__stack
        == 0
        ;
}

static inline
Index__u32 *GL_get_p_index_of__framebuffer_on__stack(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager) {
    return &p_GL_framebuffer_manager
        ->index_of__framebuffer_on__stack;
}

static inline
GL_Framebuffer **GL_get_p_ptr_framebuffer_by__index_from__stack_of__manager(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager,
        Index__u32 index_of__GL_framebuffer) {
    return &p_GL_framebuffer_manager
        ->GL_ptr_array__framebuffer_stack[index_of__GL_framebuffer];
}


#endif
