
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

#include <entity/controllers/controller_player.h>
#include <entity/controllers/controller_dummy.h>
#include <input/input.h>

#include <world/generators/generator_flat_world.h>
#include <game.h>
#include <entity/entity_manager.h>

Game game;

int main(void) {
    PLATFORM_init_gfx_context(&game.gfx_context);
    PLATFORM_init_rendering__game(&game.gfx_context);

    init_weight_map();
    init_world_parameters(&game.world_params, 
            chunk_generator__flat_world_f, 0);

    init_chunk_manager(&game.chunk_manager,
            &game.world_params);

    for (uint8_t i=0;i<96;i++) {
        Entity *skeleton =
            get_new__entity(&game.entity_manager,
                    Entity_Kind__Skeleton);
        skeleton->controller_handler =
            m_controller_for__dummy;
    }

    game.local_player = get_new__player(&game.entity_manager);
    set_entity__is_not_updating_position(game.local_player);

    game.local_player->controller_handler =
        m_controller_for__player;
    set_entity__armor(game.local_player,
            Entity_Armor_Kind__Cloth,
            Entity_Armor_Modification_Kind__None);

    move_chunk_manager__chunks(
            &game.chunk_manager, 
            &game.world_params, 
            DIRECTION__NORTH,
            2);
    PLATFORM_update_chunks(
            &game.gfx_context,
            &game.chunk_manager);

	while(1) {
        //swiWaitForVBlank();
        manage_game(&game);
        if (is_input__game_settings(&game)) break;
	}

    return 0;
}
