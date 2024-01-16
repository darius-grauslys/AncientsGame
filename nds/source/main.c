
#include <nds.h>
#include <nds/arm9/background.h>
#include <assets/tiles.h>
#include <defines.h>
#include <world/chunk.h>
#include <world/tile.h>
#include <world/chunk_manager.h>
#include <world/world_parameters.h>
#include <entity/entity.h>
#include <rendering/rendering.h>

#include <assets/entities/player.h>
#include <assets/entities/skeleton.h>
#include <assets/entities/zombie.h>

#include <world/generators/generator_flat_world.h>

// 2bytes ppx, 8x8 pixel per tile, 8x8 tiles per chunk
// thats 2x64x64, but we need to fit in 128x128, so *2*2
unsigned short gfx_chunk[8 * 8 * 8 * 8 * 2 * 2] = { 0 };

Chunk_Manager chunk_manager;
World_Parameters world_params;

void chunk_generator(World_Parameters *world_params, Chunk *chunk) {

    uint32_t tile_index = 
        (((chunk->x % 32) + 32) % 32)
        + (((chunk->y % 32) + 32) % 32) * 32;

    for (uint32_t i=0;i<CHUNK_QUANTITY_OF__TILES;i++) {
        chunk->tiles[i].the_kind_of_tile__this_tile_is =
            (enum Tile_Kind)tile_index;
    }
}

int main(void) {
    PLATFORM_Gfx_Context gfx_context;
    PLATFORM_init_gfx_context(&gfx_context);
    PLATFORM_init_rendering__game(&gfx_context);

    init_world_parameters(&world_params, 
            chunk_generator__flat_world_f, 0);

    init_chunk_manager(&chunk_manager,
            &world_params);

    // init_entity(&player, Entity_Kind__Skeleton);
	// dmaCopy(skeletonPal, SPRITE_PALETTE, 512);
    // oamSet(&oamMain, 0, 0, 0, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, 
    //     player.sprite_wrapper.sprite.sprite_texture.gfx, -1, false, false, false, false, false);

    PLATFORM_update_chunks(
            &gfx_context,
            &chunk_manager);

    // move_chunk_manager__chunks(
    //         &chunk_manager,
    //         &world_params,
    //         DIRECTION__EAST,
    //         1);

    // Chunk_Manager__Chunk_Map_Node *node =
    //     chunk_manager.chunk_map_node__most_north_western;
    // node =
    //     node->chunk_map_node__south;
    // for (int i=0;i<8;i++) {
    //     debug_info("node->x,y: %d, %d", 
    //             node->chunk__here->x,
    //             node->chunk__here->y);
    //     node = node->chunk_map_node__east;
    // }


    int32_t center_x = 0, center_y = 0;

    bool drop = false;

	while(1) {
		swiWaitForVBlank();
		scanKeys();
		int keys = keysHeld();
		if (keys & KEY_START) break;

		if(keys & KEY_UP) center_y--;
		if(keys & KEY_DOWN) center_y++;
	
		if(keys & KEY_LEFT) center_x--;
		if(keys & KEY_RIGHT) center_x++;

        if(keys & KEY_A && !drop) {
            drop = true;
            move_chunk_manager__chunks(
                    &chunk_manager, 
                    &world_params, 
                    DIRECTION__EAST,
                    1);
            PLATFORM_update_chunks(
                    &gfx_context,
                    &chunk_manager);
        } else if(keys & KEY_B && !drop) {
            drop = true;
            move_chunk_manager__chunks(
                    &chunk_manager, 
                    &world_params, 
                    DIRECTION__SOUTH,
                    1);
            PLATFORM_update_chunks(
                    &gfx_context,
                    &chunk_manager);
        } else if(keys & KEY_Y && !drop) {
            drop = true;
            move_chunk_manager__chunks(
                    &chunk_manager, 
                    &world_params, 
                    DIRECTION__WEST,
                    1);
            PLATFORM_update_chunks(
                    &gfx_context,
                    &chunk_manager);
        } else if(keys & KEY_X && !drop) {
            drop = true;
            move_chunk_manager__chunks(
                    &chunk_manager, 
                    &world_params, 
                    DIRECTION__NORTH,
                    1);
            PLATFORM_update_chunks(
                    &gfx_context,
                    &chunk_manager);
        } else if (!keys) {
            drop = false;
        }

		bgSetScroll(
                gfx_context.active_background_ground__buffer->
                background_index,
                center_x, center_y);
		bgUpdate();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}

    return 0;
}
