#include <nds.h>
#include <rendering/render_tile.h>
#include <platform_defines.h>
#include <world/tile.h>

void PLATFORM_render_tile__row(TextureAtlas textureAtlas,
        RenderTarget target,
        Tile *tile,
        uint32_t row,
        uint32_t offset) {
    NDS_RenderTarget *nds_target = (NDS_RenderTarget*)target;
    while (DMA_CR(nds_target->dma_channel) & DMA_BUSY);
    uint32_t offset_from_source = 
        TILE_WIDTH__IN_BYTES / 2
        * get_tile_texture_sheet_index(tile)
        + (TILE_SHEET_WIDTH__IN_BYTES / 2
                * row);
    dmaCopy((unsigned short*)textureAtlas + offset_from_source,
            (unsigned short*)nds_target->destination + offset, 16);
}
