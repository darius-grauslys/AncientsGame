#include <rendering/chunk_renderer.h>
#include <rendering/framebuffer.h>
#include <rendering/glad/glad.h>
#include <stdint.h>

#include <world/chunk.h>
#include <world/tile.h>

void render_chunk(Chunk *chunk, 
        void *framebuffer_source, 
        void *framebuffer_target) {
    Framebuffer *pframebuffer_source = (Framebuffer*)framebuffer_source;
    Framebuffer *pframebuffer_target = (Framebuffer*)framebuffer_target;
    
    use_framebuffer_for__read(pframebuffer_source);
    use_framebuffer_for__draw(pframebuffer_target);

    for (uint32_t i=0;i<CHUNK__QUANTITY_OF_TILES;i++) {
        Tile *tile = &chunk->tiles[i];
        uint32_t tile_sheet_index =
            get_tile_sheet_index(tile);

        bool is_structure_tile =
            tile_sheet_index < QUANTITY_OF_TILES__IN_TILE_SHEET_ROW;

        //TODO: remove the usage of tile->flags below. It is only here
        //for debugging.

        uint32_t src_x1 =
            TILE_PIXEL_WIDTH *
            (tile_sheet_index % QUANTITY_OF_TILES__IN_TILE_SHEET_ROW);
        uint32_t src_y1 =
            TILE_SHEET_PIXEL_HEIGHT -
            TILE_PIXEL_HEIGHT -
            TILE_PIXEL_HEIGHT *
            (tile->flags + (tile_sheet_index / QUANTITY_OF_TILES__IN_TILE_SHEET_ROW));
        uint32_t src_x2 =
            src_x1 + TILE_PIXEL_WIDTH;
        uint32_t src_y2 =
            src_y1 + TILE_PIXEL_HEIGHT;

        uint32_t dst_x1 =
            TILE_PIXEL_WIDTH *
            (i % CHUNK__WIDTH);
        uint32_t dst_y1 =
            TILE_PIXEL_HEIGHT *
            (i / CHUNK__WIDTH);
        uint32_t dst_x2 =
            dst_x1 + TILE_PIXEL_WIDTH;
        uint32_t dst_y2 =
            dst_y1 + TILE_PIXEL_HEIGHT;
        glBlitFramebuffer(
                src_x1, src_y1, src_x2, src_y2,
                dst_x1, dst_y1, dst_x2, dst_y2,
                GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
}
