#include "sdl_event.h"
#include <platform.h>
#include <game.h>

void PLATFORM_pre_render(Game *p_game) {
    poll_sdl_event(p_game);
}

void PLATFORM_post_render(Game *p_game) {
    Camera *p_camera =
        &p_game->world.camera;
}
