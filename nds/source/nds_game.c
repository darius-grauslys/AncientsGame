#include "input/input.h"
#include <nds.h>
#include <game.h>
#include <defines.h>
#include <collisions/hitbox_aabb.h>

void PLATFORM_pre_render(Game *p_game) {
    swiWaitForVBlank();
}
void PLATFORM_post_render(Game *p_game) {
    Entity *p_player =
        p_game->world.entity_manager.p_local_player;
    if (!p_player)
        return;
    // TODO: magic numbers to put player in correct spot.
    bgSetScroll(
        p_game->gfx_context.background_ground
        .background_index,
        get_global_x_from__hitbox(&p_player->hitbox) - 126,
        -get_global_y_from__hitbox(&p_player->hitbox) - 38
        );
    bgSetScroll(
        p_game->gfx_context.background_ground__overlay
        .background_index,
        get_global_x_from__hitbox(&p_player->hitbox) - 126,
        -get_global_y_from__hitbox(&p_player->hitbox) - 38
        );
    bgSetScroll(
        p_game->gfx_context.background_ground__sprite_cover
        .background_index,
        get_global_x_from__hitbox(&p_player->hitbox) - 126,
        -get_global_y_from__hitbox(&p_player->hitbox) - 30
        );
	
    bgUpdate();

    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
}
