#include <rendering/framebuffer.h>
#include <rendering/glad/glad.h>

void init_framebuffer(Framebuffer *framebuffer) {
    glGenFramebuffers(1, &framebuffer->handle);
}
void set_framebuffer__color_attachment__with_a_texture(
        Framebuffer *framebuffer,
        Texture *texture) {
    set_framebuffer__color_attachment__with_a_texture__without_unbinding(
            framebuffer, texture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void set_framebuffer__color_attachment__with_a_texture__without_unbinding(
        Framebuffer *framebuffer,
        Texture *texture) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
            GL_TEXTURE_2D, texture->handle, 0);
}
void release_framebuffer(Framebuffer *framebuffer) {
    glDeleteFramebuffers(1, &framebuffer->handle);
    framebuffer->handle = 0;
}
void use_framebuffer(Framebuffer *framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);
}
