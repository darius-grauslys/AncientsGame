
#include <nds.h>
#include <nds/arm9/background.h>
#include <assets/tiles.h>
#include <defines.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <rendering/render_chunk.h>
#include <rendering/sprite.h>
#include <entity/entity.h>

#include <assets/entities/player.h>

// 2bytes ppx, 8x8 pixel per tile, 8x8 tiles per chunk
// thats 2x64x64, but we need to fit in 128x128, so *2*2
unsigned short gfx_chunk[8 * 8 * 8 * 8 * 2 * 2] = { 0 };

Chunk chunk;

int main(void) {

    videoSetMode(MODE_5_2D);
	// set the sub background up for text display (we could just print to one
	// of the main display text backgrounds just as easily
	videoSetModeSub(MODE_0_2D); //sub bg 0 will be used to print text

	//vram banks are somewhat complex
	vramSetPrimaryBanks(VRAM_A_MAIN_BG_0x06000000, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);

    // render oak_wood_planks into the chunk.
    // for (int tile_x=0;tile_x<16;tile_x++) {
    //     for (int tile_y=0;tile_y<16;tile_y++) {
    //         render_tile(tile_x, tile_y);
    //     }
    // }

	consoleDemoInit();

    RenderTarget target;
    RenderTarget source;
    target.destination = gfx_chunk;
    target.dma_channel = 0;
    target.offset = 0;
    target.target_row_stride = CHUNK_WIDTH__IN_BYTES / 2;

    source.destination = (unsigned short*)tilesBitmap;
    source.dma_channel = 0;
    source.offset = 0;
    source.target_row_stride = TILE_SHEET_WIDTH__IN_BYTES / 2;

    init_chunk(&chunk, 0, 0);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	dmaCopy(playerPal, SPRITE_PALETTE, 512);

    Entity player;

    init_entity(&player, Entity_Kind__Player);
    oamSet(&oamMain, 0, 0, 0, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, 
        player.sprite_wrapper.sprite.sprite_texture.gfx, -1, false, false, false, false, false);

    for (int i=0;i<CHUNK_QUANTITY_OF__TILES;i++)
        init_tile(&chunk.tiles[i], Tile_Kind__Grass, TILE_FLAGS__NONE);

    init_tile(&chunk.tiles[13], Tile_Kind__Iron, TILE_FLAGS__NONE);
    init_tile(&chunk.tiles[11], Tile_Kind__Stone_Brick, TILE_FLAGS__NONE);

    PLATFORM_render_chunk(
            &source,
            &target, &chunk);

	// set up our bitmap background
	bgInit(3, BgType_Bmp16, BgSize_B16_128x128, 0,0);
    dmaCopy(gfx_chunk, BG_GFX, sizeof(gfx_chunk));
	
	while(1) {
		swiWaitForVBlank();
		scanKeys();
		if (keysDown()&KEY_START) break;

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}

    return 0;
}
