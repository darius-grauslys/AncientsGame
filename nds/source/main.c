
#include <nds.h>
#include <nds/arm9/background.h>
#include <assets/tiles.h>
#include <defines.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <entity/entity.h>
#include <rendering/rendering.h>

#include <assets/entities/player.h>
#include <assets/entities/skeleton.h>
#include <assets/entities/zombie.h>

// 2bytes ppx, 8x8 pixel per tile, 8x8 tiles per chunk
// thats 2x64x64, but we need to fit in 128x128, so *2*2
unsigned short gfx_chunk[8 * 8 * 8 * 8 * 2 * 2] = { 0 };

Chunk_Manager chunk_manager;

int main(void) {
    PLATFORM_Gfx_Context gfx_context;
    PLATFORM_init_gfx_context(&gfx_context);
    PLATFORM_init_rendering__game(&gfx_context);

    init_chunk(&chunk_manager.chunk, 0, 0);
    Chunk *chunk = &chunk_manager.chunk;

    Entity player;

    init_entity(&player, Entity_Kind__Skeleton);
	dmaCopy(skeletonPal, SPRITE_PALETTE, 512);
    player.armor_properties.the_kind_of_armor__this_armor_is =
        Entity_Armor_Kind__Cloth;
    player.armor_properties.the_kind_of_modification__this_armor_has =
        Entity_Armor_Modification_Kind__None;
    set_animation__of_entity(&player, Sprite_Animation_Kind__Humanoid__Walk);
    oamSet(&oamMain, 0, 0, 0, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, 
        player.sprite_wrapper.sprite.sprite_texture.gfx, -1, false, false, false, false, false);

    for (int i=0;i<CHUNK_QUANTITY_OF__TILES;i++)
        init_tile(&chunk->tiles[i], Tile_Kind__Grass, TILE_FLAGS__NONE);

    init_tile(&chunk->tiles[13], Tile_Kind__Iron, TILE_FLAGS__NONE);
    init_tile(&chunk->tiles[11], Tile_Kind__Stone_Brick, TILE_FLAGS__NONE);

    PLATFORM_update_chunks(
            &gfx_context,
            &chunk_manager);

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
                    set_entity__armor(&player,
                            Entity_Armor_Kind__Cloth,
                            Entity_Armor_Modification_Kind__None);
                    break;
                case Entity_Armor_Kind__Cloth:
                    set_entity__armor(&player,
                            Entity_Armor_Kind__Iron,
                            Entity_Armor_Modification_Kind__None);
                    break;
                case Entity_Armor_Kind__Iron:
                    switch (player.armor_properties.the_kind_of_modification__this_armor_has) {
                        case Entity_Armor_Modification_Kind__None:
                            set_entity__armor(&player,
                                    Entity_Armor_Kind__Iron,
                                    Entity_Armor_Modification_Kind__Diamond);
                            break;
                        case Entity_Armor_Modification_Kind__Diamond:
                            set_entity__armor(&player,
                                    Entity_Armor_Kind__Iron,
                                    Entity_Armor_Modification_Kind__Amethyst);
                            break;
                        case Entity_Armor_Modification_Kind__Amethyst:
                            set_entity__armor(&player,
                                    Entity_Armor_Kind__Gold,
                                    Entity_Armor_Modification_Kind__None);
                            break;
                    }
                    break;
                case Entity_Armor_Kind__Gold:
                    switch (player.armor_properties.the_kind_of_modification__this_armor_has) {
                        case Entity_Armor_Modification_Kind__None:
                            set_entity__armor(&player,
                                    Entity_Armor_Kind__Gold,
                                    Entity_Armor_Modification_Kind__Diamond);
                            break;
                        case Entity_Armor_Modification_Kind__Diamond:
                            set_entity__armor(&player,
                                    Entity_Armor_Kind__Gold,
                                    Entity_Armor_Modification_Kind__Amethyst);
                            break;
                        case Entity_Armor_Modification_Kind__Amethyst:
                            set_entity__armor(&player,
                                    Entity_Armor_Kind__None,
                                    Entity_Armor_Modification_Kind__None);
                            break;
                    }
                    break;
            }
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
