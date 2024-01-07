#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>

typedef struct Texture_t {
    uint32_t handle;
    uint32_t width, height;
    uint8_t channel_count;
} Texture;

void init_texture(Texture *texture);
void init_texture__with_path(Texture *texture, 
        const char *path);

void release_texture(Texture *texture);

#endif
