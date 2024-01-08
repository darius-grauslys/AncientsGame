#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

typedef struct Texture_t {
    uint32_t handle;
    uint32_t width, height;
    uint32_t channel_count;
} Texture;

void init_texture(Texture *texture);
void init_texture__with_size(Texture *texture,
        uint32_t width, uint32_t height);
void init_texture__with_path(Texture *texture, 
        const char *path);
void use_texture(Texture *texture);

void release_texture(Texture *texture);

#endif
