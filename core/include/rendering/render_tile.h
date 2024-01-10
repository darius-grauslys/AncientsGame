#ifndef RENDER_TILE_H
#define RENDER_TILE_H

#include <defines.h>

///
/// As we render a chunk, we will scan left to right
/// rendering a row of a tile at a time.
///

void PLATFORM_render_tile__row(
        TextureAtlas texture_atlas,
        RenderTarget target,
        Tile *tile,
        uint32_t row,
        uint32_t offset);

#endif
