#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

typedef struct PLATFORM_Texture_t PLATFORM_Texture;

typedef struct Framebuffer_t {
    uint32_t handle;
    uint32_t handle__render_buffer;
} Framebuffer;

void initialize_framebuffer(Framebuffer *framebuffer);
void set_framebuffer__color_attachment__with_a_texture(
        Framebuffer *framebuffer,
        PLATFORM_Texture *texture);
void release_framebuffer(Framebuffer *framebuffer);
void use_framebuffer_for__read_and_draw(Framebuffer *framebuffer);
void use_framebuffer_for__read(Framebuffer *framebuffer);
void use_framebuffer_for__draw(Framebuffer *framebuffer);

#endif
