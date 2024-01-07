#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <rendering/texture.h>

typedef struct Framebuffer_t {
    uint32_t handle;
} Framebuffer;

void init_framebuffer(Framebuffer *framebuffer);
void set_framebuffer__color_attachment__with_a_texture(
        Framebuffer *framebuffer,
        Texture *texture);
void set_framebuffer__color_attachment__with_a_texture__without_unbinding(
        Framebuffer *framebuffer,
        Texture *texture);
void release_framebuffer(Framebuffer *framebuffer);
void use_framebuffer(Framebuffer *framebuffer);

#endif
