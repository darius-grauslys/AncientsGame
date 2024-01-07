#ifndef PASSTHROUGH_H
#define PASSTHROUGH_H

/// 
/// This header has declarations of framebuffer helper
/// functions. 
///

#include <rendering/framebuffer.h>
#include <rendering/shader.h>

void passthrough__textures(
        Framebuffer *framebuffer,
        Texture *texture_source,
        Texture *texture_target,
        Shader_2D *shader,
        int32_t x, int32_t y);

#endif
