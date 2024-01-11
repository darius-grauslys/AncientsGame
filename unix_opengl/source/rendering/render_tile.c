#include <rendering/framebuffer.h>
#include <rendering/glad/glad.h>
#include <stdint.h>

#include <world/chunk.h>
#include <world/tile.h>

#include <platform_defines.h>

void PLATFORM_render_tile(
        RenderTarget *texture_atlas,
        RenderTarget *target,
        Tile *tile) {
    Framebuffer *pframebuffer_source = &texture_atlas->framebuffer;
    Framebuffer *pframebuffer_target = &target->framebuffer;    
    use_framebuffer_for__read(pframebuffer_source);
    use_framebuffer_for__draw(pframebuffer_target);

    uint32_t tile_sheet_index =
        get_tile_texture_sheet_index(tile);

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

    debug_info("x:%d, y:%d", target->x, target->y);
    uint32_t dst_x1 =
        TILE_PIXEL_WIDTH *
        (target->x);
    uint32_t dst_y1 =
        TILE_PIXEL_HEIGHT *
        (target->y);
    uint32_t dst_x2 =
        dst_x1 + TILE_PIXEL_WIDTH;
    uint32_t dst_y2 =
        dst_y1 + TILE_PIXEL_HEIGHT;
    glBlitFramebuffer(
            src_x1, src_y1, src_x2, src_y2,
            dst_x1, dst_y1, dst_x2, dst_y2,
            GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
