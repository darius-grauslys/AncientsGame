#include "defines_weak.h"
#include "entity/entity.h"
#include "input/input.h"
#include "nds_defines.h"
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
        p_game->p_gfx_context->backgrounds__main[
            NDS_BACKGROUND_SLOT__GAME__GROUND]
        .background_index_from__hardware,
         get_x_i32_from__camera(p_camera) - 126,
        -get_y_i32_from__camera(p_camera) - 30
        );
    // TODO: f_ui mangling occurs here
    bgSetScroll(
        p_game->p_gfx_context->backgrounds__main[
            NDS_BACKGROUND_SLOT__GAME__WALL_UPPER]
        .background_index_from__hardware,
         get_x_i32_from__camera(p_camera) - 126,
        -get_y_i32_from__camera(p_camera) - 38
        );
    // Ends here.
    bgSetScroll(
        p_game->p_gfx_context->backgrounds__main[
            NDS_BACKGROUND_SLOT__GAME__WALL_LOWER]
        .background_index_from__hardware,
         get_x_i32_from__camera(p_camera) - 126,
        -get_y_i32_from__camera(p_camera) - 30
        );
	
    bgUpdate();

    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
}
