#include <rendering/render_chunk.h>
#include <rendering/render_tile.h>
#include <world/chunk.h>
#include <world/tile.h>

void PLATFORM_render_chunk(
        RenderTarget *texture_atlas, 
        RenderTarget *target, Chunk *chunk) {

    uint32_t original_target_x =
        target->x;
    uint32_t original_target_y =
        target->y;

    for (uint32_t y=0; y < CHUNK_WIDTH__IN_TILES; y++) {
        for (uint32_t x=0; x < CHUNK_WIDTH__IN_TILES; x++) {
            Tile *tile =
                &chunk->tiles[x + CHUNK_WIDTH__IN_TILES * y];
            target->x = original_target_x + x;
            target->y = original_target_y + y;
            PLATFORM_render_tile(
                    texture_atlas,
                    target,
                    tile);
        }
    }
}
