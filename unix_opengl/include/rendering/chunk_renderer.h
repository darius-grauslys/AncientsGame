#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include <world/chunk.h>

void render_chunk(Chunk *chunk, 
        void *framebuffer_source, 
        void *framebuffer_target);

#endif
