#include <nds.h>
#include <game.h>
#include <defines.h>

void PLATFORM_pre_render(Game *game) {
    swiWaitForVBlank();
}
void PLATFORM_post_render(Game *game) {
    Entity *player =
        game->world.entity_manager.local_player;
    bgSetScroll(
        game->gfx_context.active_background_ground__buffer->
        background_index,
        (player->x__chunk << 
            ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
            + (player->x >> 
                ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE), 
        -((player->y__chunk << 
            ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
            + (player->y >> 
                ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE)));
	
    bgUpdate();

    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
}
