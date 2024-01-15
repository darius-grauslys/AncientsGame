#include <nds.h>
#include <rendering/render_tile.h>
#include <platform_defines.h>
#include <world/tile.h>

void PLATFORM_render_tile(
        PLATFORM_Gfx_Context *context,
        Tile *tile) {

    // while (DMA_CR(target->dma_channel) & DMA_BUSY);

    // dmaCopy(texture_atlas->destination + texture_atlas->offset,
    //         target->destination + target->offset, TILE_WIDTH__IN_BYTES);
}
