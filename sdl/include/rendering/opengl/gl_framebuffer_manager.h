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

#endif
