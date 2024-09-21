#include "sdl_event.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <platform.h>
#include <game.h>
#include <sdl_defines.h>

void PLATFORM_pre_render(Game *p_game) {
    SDL_PumpEvents();
    poll_sdl_event(p_game);

    SDL_RenderClear(
            get_p_PLATFORM_gfx_context_from__game(p_game)
            ->p_SDL_renderer);
}

void PLATFORM_post_render(Game *p_game) {
    Camera *p_camera =
        &p_game->world.camera;

    SDL_GL_SwapWindow(
            get_p_PLATFORM_gfx_context_from__game(
                p_game)
            ->p_SDL_window);
}
