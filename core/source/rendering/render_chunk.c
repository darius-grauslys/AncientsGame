#include <rendering/render_chunk.h>
#include <rendering/render_tile.h>
#include <world/chunk.h>

void render_chunk(
        TextureAtlas texture_atlas, 
        RenderTarget target, Chunk *chunk, 
        uint32_t offset, uint32_t target_row_stride) {
    for (uint32_t y=0; y < CHUNK_WIDTH__IN_TILES; y++) {
        for (int row=0; row < TILE_WIDTH__IN_PIXELS; row++) {
            for (uint32_t x=0; x < CHUNK_WIDTH__IN_TILES; x++) {
                uint32_t tile_index =
                    x + CHUNK_WIDTH__IN_TILES * y;
                uint32_t _offset =
                    offset
                    + (TILE_WIDTH__IN_BYTES * x)
                    + (CHUNK_WIDTH__IN_BYTES
                            * TILE_WIDTH__IN_PIXELS
                            * y);
                PLATFORM_render_tile__row(
                        texture_atlas,
                        target,
                        &(chunk->tiles[tile_index]),
                        row,
                        _offset);
            }
        }
    }
}
