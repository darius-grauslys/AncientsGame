#include "rendering/opengl/glad/glad.h"
#include <rendering/opengl/gl_framebuffer.h>
#include <rendering/opengl/gl_texture.h>

void GL_initialize_framebuffer_as__deallocated(
        GL_Framebuffer *p_GL_framebuffer) {
    GL_set_framebuffer_as__deallocated(
            p_GL_framebuffer);
}

void GL_bind_texture_to__framebuffer(
        GL_Framebuffer *p_GL_framebuffer,
        PLATFORM_Texture *p_PLATFORM_texture) {
    p_GL_framebuffer->p_PLATFORM_texture =
        p_PLATFORM_texture;

    u32 GL_format =
        GL_get_texture_format(
                p_PLATFORM_texture);

    glFramebufferTexture2D(
            GL_FRAMEBUFFER, 
            GL_COLOR_ATTACHMENT0, 
            GL_TEXTURE_2D, 
            p_PLATFORM_texture->GL_texture_handle, 
            0);

    GLenum GL_status =
        glCheckFramebufferStatus(GL_FRAMEBUFFER);

    switch (GL_status) {
        case GL_FRAMEBUFFER_COMPLETE:
            break;
        default:
            ;
            const char *p_c_str__error;
            switch (GL_status) {
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    p_c_str__error = "incomplete attachment";
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    p_c_str__error = "incomplete missing attachment";
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
                    p_c_str__error = "incomplete dimensions";
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
                    p_c_str__error = "incomplete formats";
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                    p_c_str__error = "incomplete draw buffer";
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                    p_c_str__error = "incomplete read buffer";
                    break;
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    p_c_str__error = "incomplete unsupported";
                    break;
                default:
                    p_c_str__error = "unknown error";
                    break;
            }
            debug_error("SDL::GL::GL_bind_texture_to__framebuffer, %s",
                    p_c_str__error);
            break;
    }
}

void GL_initialize_framebuffer(
        GL_Framebuffer *p_GL_framebuffer,
        PLATFORM_Texture *p_PLATFORM_texture) {
    if (p_PLATFORM_texture) {
        GL_bind_texture_to__framebuffer(
                p_GL_framebuffer, 
                p_PLATFORM_texture);
    }
}

void GL_use_framebuffer_as__target(
        GL_Framebuffer *p_GL_framebuffer) {
    glBindFramebuffer(
            GL_FRAMEBUFFER,
            p_GL_framebuffer
            ->GL_framebuffer_handle);
}

void GL_unbind_framebuffer(void) {
    glBindFramebuffer(
            GL_FRAMEBUFFER,
            0);
}
