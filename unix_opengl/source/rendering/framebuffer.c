#include <rendering/framebuffer.h>
#include <rendering/glad/glad.h>
#include <debug/debug.h>

void init_framebuffer(Framebuffer *framebuffer) {
    glGenFramebuffers(1, &framebuffer->handle);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);
    // glGenRenderbuffers(1, &framebuffer->handle__render_buffer);
    // glBindRenderbuffer(GL_RENDERBUFFER, framebuffer->handle__render_buffer);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
    //         GL_RENDERBUFFER, framebuffer->handle__render_buffer);
}
void set_framebuffer__color_attachment__with_a_texture(
        Framebuffer *framebuffer,
        Texture *texture) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);

    debug_info("gen framebuffer texture_id:%d, w:%d, h:%d",
            texture->handle, texture->width, texture->height);
    
    // The depth buffer
    // GLuint depthrenderbuffer;
    // glGenRenderbuffers(1, &depthrenderbuffer);
    // glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 
    //         texture->width, texture->height);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
    
    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->handle, 0);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if ( test != GL_FRAMEBUFFER_COMPLETE )
    {
        debug_error("OpenGL Failed to create render target");
    }
}
void release_framebuffer(Framebuffer *framebuffer) {
    glDeleteFramebuffers(1, &framebuffer->handle);
    framebuffer->handle = 0;
}

void use_framebuffer_for__read_and_draw(Framebuffer *framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);
}
void use_framebuffer_for__read(Framebuffer *framebuffer) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer->handle);
}
void use_framebuffer_for__draw(Framebuffer *framebuffer) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer->handle);
}
