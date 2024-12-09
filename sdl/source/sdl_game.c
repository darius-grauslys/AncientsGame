#include "rendering/sdl_gfx_context.h"
#include "sdl_event.h"
#include "serialization/sdl_filesystem.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <platform.h>
#include <game.h>
#include <sdl_defines.h>

void PLATFORM_pre_render(Game *p_game) {
    SDL_PumpEvents();
    SDL_poll_event(p_game);

    SDL_poll_serialization_requests(p_game);
    SDL_clear_screen(
            get_p_PLATFORM_gfx_context_from__game(p_game));
}

void PLATFORM_post_render(Game *p_game) {
    Camera *p_camera =
        &p_game->world.camera;

    SDL_GL_SwapWindow(
            get_p_PLATFORM_gfx_context_from__game(
                p_game)
            ->p_SDL_window);
}
