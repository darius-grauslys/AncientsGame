#include <nds.h>
#include <game.h>
#include <defines.h>
#include <collisions/hitbox_aabb.h>

void PLATFORM_pre_render(Game *game) {
    swiWaitForVBlank();
}
void PLATFORM_post_render(Game *game) {
    Entity *player =
        game->world.entity_manager.local_player;
    // TODO: magic numbers to put player in correct spot.
    bgSetScroll(
        game->gfx_context.active_background_ground__buffer->
        background_index,
        get_global_x_from__hitbox(&player->hitbox) - 123,
        -get_global_y_from__hitbox(&player->hitbox) - 104
        );
	
    bgUpdate();

    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
}
