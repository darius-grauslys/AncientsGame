#include <rendering/render_chunk.h>
#include <rendering/render_tile.h>
#include <world/chunk.h>
#include <world/tile.h>

void PLATFORM_render_chunk(
        PLATFORM_Gfx_Context *context,
        Chunk *chunk) {

    // uint32_t original_target_offset =
    //     target->offset;
    // for (uint32_t y=0; y < CHUNK_WIDTH__IN_TILES; y++) {
    //     for (int row=0; row < TILE_WIDTH__IN_PIXELS; row++) {
    //         for (uint32_t x=0; x < CHUNK_WIDTH__IN_TILES; x++) {
    //             Tile *tile =
    //                 &chunk->tiles[x + CHUNK_WIDTH__IN_TILES * y];
    //             target->offset =
    //                 original_target_offset
    //                 + (TILE_WIDTH__IN_BYTES / 2 * x)
    //                 + (CHUNK_WIDTH__IN_BYTES 
    //                         * ((TILE_WIDTH__IN_PIXELS
    //                         * y)
    //                         + row));
    //             texture_atlas->offset = 
    //                 TILE_WIDTH__IN_BYTES / 2
    //                 * get_tile_texture_sheet_index(tile)
    //                 + (TILE_SHEET_WIDTH__IN_BYTES
    //                         * row);

    //             PLATFORM_render_tile(
    //                     texture_atlas,
    //                     target,
    //                     tile);
    //         }
    //     }
    // }
}
