#include "defines_weak.h"
#include "entity/entity.h"
#include "input/input.h"
#include "world/camera.h"
#include <nds.h>
#include <game.h>
#include <defines.h>
#include <collisions/hitbox_aabb.h>

void PLATFORM_pre_render(Game *p_game) {
    swiWaitForVBlank();
}
void PLATFORM_post_render(Game *p_game) {
    Camera *p_camera =
        &p_game->world.camera;

    bgSetScroll(
        p_game->gfx_context.background_ground
        .background_index,
         get_x_i32_from__camera(p_camera) - 126,
        -get_y_i32_from__camera(p_camera) - 38
        );
    bgSetScroll(
        p_game->gfx_context.background_ground__overlay
        .background_index,
         get_x_i32_from__camera(p_camera) - 126,
        -get_y_i32_from__camera(p_camera) - 38
        );
    bgSetScroll(
        p_game->gfx_context.background_ground__sprite_cover
        .background_index,
         get_x_i32_from__camera(p_camera)  - 126,
        -get_y_i32_from__camera(p_camera) - 30
        );
	
    bgUpdate();

    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
}
