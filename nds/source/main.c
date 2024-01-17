
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

#include <entity/controllers/controller_player.h>
#include <input/input.h>

#include <world/generators/generator_flat_world.h>

Game game;

int main(void) {
    PLATFORM_init_gfx_context(&game.gfx_context);
    PLATFORM_init_rendering__game(&game.gfx_context);

    init_weight_map();
    init_world_parameters(&game.world_params, 
            chunk_generator__flat_world_f, 0);

    init_chunk_manager(&game.chunk_manager,
            &game.world_params);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

    Entity player;

    init_entity(&player, Entity_Kind__Player);
	dmaCopy(playerPal, SPRITE_PALETTE, 512);
    oamSet(&oamMain, 0, 127 - 8, 96 - 8, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, 
        player.sprite_wrapper.sprite.sprite_texture.gfx, -1, false, false, false, false, false);

    player.controller_handler =
        controller__player;
    set_entity__armor(&player,
            Entity_Armor_Kind__Cloth,
            Entity_Armor_Modification_Kind__None);

    move_chunk_manager__chunks(
            &game.chunk_manager, 
            &game.world_params, 
            DIRECTION__SOUTH,
            4);
    move_chunk_manager__chunks(
            &game.chunk_manager, 
            &game.world_params, 
            DIRECTION__NORTH,
            1);
    PLATFORM_update_chunks(
            &game.gfx_context,
            &game.chunk_manager);

    int32_t center_x = 0, center_y = 0;

    uint32_t frame_tick = 0;

    Direction direction__move_chunks = DIRECTION__NONE;

	while(1) {
		swiWaitForVBlank();
        PLATFORM_poll_input(&game);
        player.controller_handler(&player, &game);

        if (frame_tick++ % 8 == 0) {
            animate_entity(&player);
        }

		if (is_input__game_settings(&game)) break;

        int32_t dx = player.x >> 6;
        int32_t dy = player.y >> 6;

        direction__move_chunks = DIRECTION__NONE;

        if (dx != center_x || dy != center_y) {
            if (center_x < dx) {
                direction__move_chunks |=
                    DIRECTION__EAST;
            } else if (center_x > dx) {
                direction__move_chunks |=
                    DIRECTION__WEST;
            }
            if (center_y > dy) {
                direction__move_chunks |=
                    DIRECTION__NORTH;
            } else if (center_y < dy) {
                direction__move_chunks |=
                    DIRECTION__SOUTH;
            }
            center_x = dx;
            center_y = dy;
        }
	
        if(direction__move_chunks != DIRECTION__NONE) {
            move_chunk_manager__chunks(
                    &game.chunk_manager, 
                    &game.world_params, 
                    direction__move_chunks,
                    1);
            PLATFORM_update_chunks(
                    &game.gfx_context,
                    &game.chunk_manager);
        }

		bgSetScroll(
                game.gfx_context.active_background_ground__buffer->
                background_index,
                player.x, -player.y);
		bgUpdate();

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
	}

    return 0;
}
