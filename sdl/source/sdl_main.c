#include "debug/opengl/gl_debug.h"
#include "input/sdl_input.h"
#include "platform_defines.h"
#include "rendering/sdl_gfx_context.h"
#include "scene/scene_manager.h"
#include "scene/sdl_scene_manager.h"
#include "sdl_event.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <platform.h>
#include <SDL2/SDL.h>
#include <game.h>
#include <scene/scene_manager.h>
#include <sdl_defines.h>
#include <rendering/opengl/glad/glad.h>

int PLATFORM_main(Game *p_game) {
    SDL_Init(
            SDL_INIT_TIMER
            | SDL_INIT_VIDEO
            | SDL_INIT_AUDIO
            | SDL_INIT_EVENTS);

    SDL_initialize_gfx_context(
            p_game,
            SDL_Gfx_Sub_Context__OpenGL_3_0);
    SDL_initialize_events();
    SDL_initialize_input_bindings();

    p_game->p_PLATFORM_gfx_context =
        &__SDL_Gfx_Context;

    SDL_establish_scenes(
            get_p_scene_manager_from__game(p_game));

    int exit_code = 
        run_game(p_game);

    SDL_dispose_gfx_context(
            get_p_PLATFORM_gfx_context_from__game(p_game));
    SDL_Quit();

    return exit_code;
}
