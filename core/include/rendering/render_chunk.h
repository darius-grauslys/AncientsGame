#ifndef RENDER_CHUNK_H
#define RENDER_CHUNK_H

#include <defines.h>

/// 
/// Render a chunk using a texture_atlas
/// onto a given RenderTarget.
///
/// RenderTarget is an opaque pointer, which is defined
/// via a backend implementation.
///

void PLATFORM_render_chunk(
        RenderTarget *texture_atlas,
        RenderTarget *target,
        Chunk *chunk);

#endif
