
#include <nds.h>
#include <nds/arm9/background.h>
#include <assets/tiles.h>
#include <defines.h>
#include <world/chunk.h>
#include <rendering/render_chunk.h>

// 2bytes ppx, 8x8 pixel per tile, 8x8 tiles per chunk
// thats 2x64x64, but we need to fit in 128x128, so *2*2
unsigned short gfx_chunk[8 * 8 * 8 * 8 * 2 * 2] = { 0 };

Chunk chunk;

void render_tile(int x, int y) {
    for (int i=0;i<8;i++) {
        dmaCopy(((const unsigned short*)tilesBitmap) + (256 * i), 
                gfx_chunk + (128 * (i + (8*y))) + (8 * x) , 16);
    }
}

int main(void) {

    videoSetMode(MODE_5_2D);
    videoSetModeSub(MODE_0_2D);

    // I think I want to use their BGCTRL[..] stuff
    vramSetBankA(VRAM_A_MAIN_BG);

    // render oak_wood_planks into the chunk.
    for (int tile_x=0;tile_x<16;tile_x++) {
        for (int tile_y=0;tile_y<16;tile_y++) {
            render_tile(tile_x, tile_y);
        }
    }

    NDS_RenderTarget target;
    target.destination = (void *)gfx_chunk;
    target.dma_channel = 0;

    render_chunk((TextureAtlas)tilesBitmap,
            (RenderTarget)&target, &chunk, 0, 
            128);

    init_chunk(&chunk, 0, 0);


	// set up our bitmap background
	bgInit(3, BgType_Bmp16, BgSize_B16_128x128, 0,0);
    dmaCopy(gfx_chunk, BG_GFX, sizeof(gfx_chunk));
	
	while(1) {
		swiWaitForVBlank();
		scanKeys();
		if (keysDown()&KEY_START) break;
	}

    return 0;
}
