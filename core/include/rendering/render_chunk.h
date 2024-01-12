#ifndef RENDER_CHUNK_H
#define RENDER_CHUNK_H

#include <defines.h>

///
/// TODO: we will want to rethink
/// the render_chunk and render_tile.
///
/// NDS wants to just use a tiled background
/// and PC wants to use openGL rect with uv's.
///
/// not quite sure how to best manage this atm.
///

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
