
#include <nds.h>
#include <nds/arm9/background.h>
#include <assets/tiles.h>
#include <defines.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <rendering/render_chunk.h>
#include <rendering/render_entity.h>
#include <rendering/sprite.h>
#include <entity/entity.h>
#include <rendering/animate_sprite.h>

#include <assets/entities/player.h>
#include <assets/entities/skeleton.h>
#include <assets/entities/zombie.h>

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


    Entity player;

    init_entity(&player, Entity_Kind__Skeleton);
	dmaCopy(skeletonPal, SPRITE_PALETTE, 512);
    player.armor_properties.the_kind_of_armor__this_armor_is =
        Entity_Armor_Kind__Cloth;
    player.armor_properties.the_kind_of_modification__this_armor_has =
        Entity_Armor_Modification_Kind__None;
    set_sprite__animation(&player, Sprite_Animation_Kind__Humanoid__Use);
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

    int i=0;

	while(1) {
		swiWaitForVBlank();
		scanKeys();
		if (keysDown()&KEY_START) break;

        if (keysDown() & KEY_B) {
            switch (player.sprite_wrapper.direction) {
                case Direction__East:
                    player.sprite_wrapper.direction = Direction__South;
                    break;
                case Direction__South:
                    player.sprite_wrapper.direction = Direction__West;
                    break;
                case Direction__West:
                    player.sprite_wrapper.direction = Direction__North;
                    break;
                case Direction__North:
                    player.sprite_wrapper.direction = Direction__East;
                    break;
            }
        }

        if (keysDown() & KEY_A) {
            switch (player.armor_properties.the_kind_of_armor__this_armor_is) {
                default:
                case Entity_Armor_Kind__None:
                    player.armor_properties.the_kind_of_armor__this_armor_is =
                        Entity_Armor_Kind__Cloth;
                    break;
                case Entity_Armor_Kind__Cloth:
                    player.armor_properties.the_kind_of_armor__this_armor_is =
                        Entity_Armor_Kind__Iron;
                    break;
                case Entity_Armor_Kind__Iron:
                    switch (player.armor_properties.the_kind_of_modification__this_armor_has) {
                        case Entity_Armor_Modification_Kind__None:
                            player.armor_properties.the_kind_of_modification__this_armor_has =
                                Entity_Armor_Modification_Kind__Diamond;
                            break;
                        case Entity_Armor_Modification_Kind__Diamond:
                            player.armor_properties.the_kind_of_modification__this_armor_has =
                                Entity_Armor_Modification_Kind__Amethyst;
                            break;
                        case Entity_Armor_Modification_Kind__Amethyst:
                            player.armor_properties.the_kind_of_modification__this_armor_has =
                                Entity_Armor_Modification_Kind__None;
                            player.armor_properties.the_kind_of_armor__this_armor_is =
                                Entity_Armor_Kind__Gold;
                            break;
                    }
                    break;
                case Entity_Armor_Kind__Gold:
                    switch (player.armor_properties.the_kind_of_modification__this_armor_has) {
                        case Entity_Armor_Modification_Kind__None:
                            player.armor_properties.the_kind_of_modification__this_armor_has =
                                Entity_Armor_Modification_Kind__Diamond;
                            break;
                        case Entity_Armor_Modification_Kind__Diamond:
                            player.armor_properties.the_kind_of_modification__this_armor_has =
                                Entity_Armor_Modification_Kind__Amethyst;
                            break;
                        case Entity_Armor_Modification_Kind__Amethyst:
                            player.armor_properties.the_kind_of_modification__this_armor_has =
                                Entity_Armor_Modification_Kind__None;
                            player.armor_properties.the_kind_of_armor__this_armor_is =
                                Entity_Armor_Kind__None;
                            break;
                    }
                    break;
            }
            set_sprite__animation(&player,
                    player.sprite_wrapper.the_kind_of_animation__this_sprite_has);
        }

        if (i++ > 100) {
            animate_entity(&player);
            i = 0;
        }

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}

    return 0;
}
