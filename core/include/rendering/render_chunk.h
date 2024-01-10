#ifndef RENDER_CHUNK_H
#define RENDER_CHUNK_H

#include <defines.h>

void render_chunk(TextureAtlas textureAtlas,
        RenderTarget target,
        Chunk *chunk,
        uint32_t offset,
        uint32_t target_row_stride);

#endif
