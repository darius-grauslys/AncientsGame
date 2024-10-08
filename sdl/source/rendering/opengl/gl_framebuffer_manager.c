#include "defines_weak.h"
#include "platform.h"
#include "rendering/opengl/gl_defines.h"
#include "rendering/opengl/gl_framebuffer.h"
#include "rendering/opengl/glad/glad.h"
#include <rendering/opengl/gl_framebuffer_manager.h>

void GL_initialize_framebuffer_manager(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager) {
    for (Index__u16 index_of__GL_framebuffer = 0;
            index_of__GL_framebuffer < MAX_QUANTITY_OF__FRAMEBUFFERS;
            index_of__GL_framebuffer++) {
        GL_Framebuffer *p_GL_framebuffer =
            &p_GL_framebuffer_manager->GL_framebuffers[index_of__GL_framebuffer];

        GL_set_framebuffer_as__deallocated(
                p_GL_framebuffer);
    }
}

GL_Framebuffer *GL_allocate_framebuffer_with__framebuffer_manager(
        GL_Framebuffer_Manager *p_GL_framebuffer_manager) {
    for (Index__u16 index_of__GL_framebuffer = 0;
            index_of__GL_framebuffer < MAX_QUANTITY_OF__FRAMEBUFFERS;
            index_of__GL_framebuffer++) {
        GL_Framebuffer *p_GL_framebuffer =
            &p_GL_framebuffer_manager
            ->GL_framebuffers[index_of__GL_framebuffer];
        if (GL_is_framebuffer_allocated(p_GL_framebuffer))
            continue;

        glCreateFramebuffers(
                1,
                &p_GL_framebuffer->GL_framebuffer_handle);

        if (!p_GL_framebuffer->GL_framebuffer_handle) {
            debug_error("SDL::GL::GL_allocate_framebuffer_with__framebuffer_manager, failed to create framebuffer.");
            return 0;
        }
        
        GL_set_framebuffer_as__allocated(
                p_GL_framebuffer);

        return p_GL_framebuffer;
    }
    return 0;
}

void GL_release_framebuffer_from__framebuffer_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Framebuffer_Manager *p_GL_framebuffer_manager,
        GL_Framebuffer *p_GL_framebuffer) {
#ifndef NDEBUG
    int index = p_GL_framebuffer
        - p_GL_framebuffer_manager->GL_framebuffers
        ;
    if (index < 0
            || index >= MAX_QUANTITY_OF__FRAMEBUFFERS) {
        debug_abort("SDL::GL::GL_release_framebuffer_from__framebuffer_manager, p_GL_framebuffer is not from this manager.");
        return;
    }
#endif

    glDeleteFramebuffers(
            1,
            &p_GL_framebuffer->GL_framebuffer_handle);

    GL_set_framebuffer_as__deallocated(
            p_GL_framebuffer);
}

void GL_dispose_framebuffer_manager(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        GL_Framebuffer_Manager *p_GL_framebuffer_manager) {
    for (Index__u16 index_of__GL_framebuffer = 0;
            index_of__GL_framebuffer < MAX_QUANTITY_OF__FRAMEBUFFERS;
            index_of__GL_framebuffer++) {
        GL_Framebuffer *p_GL_framebuffer =
            &p_GL_framebuffer_manager->GL_framebuffers[index_of__GL_framebuffer];
        if (GL_is_framebuffer_allocated(
                    p_GL_framebuffer)) {
            GL_release_framebuffer_from__framebuffer_manager(
                    p_PLATFORM_gfx_context, 
                    p_GL_framebuffer_manager, 
                    p_GL_framebuffer);
        }
    }
}
