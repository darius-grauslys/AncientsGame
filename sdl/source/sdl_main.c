#include "platform_defines.h"
#include "scene/scene_manager.h"
#include "scene/sdl_scene_manager.h"
#include "sdl_event.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <platform.h>
#include <SDL2/SDL.h>
#include <game.h>
#include <scene/scene_manager.h>

int PLATFORM_main(Game *p_game) {
    SDL_Init(
            SDL_INIT_TIMER
            | SDL_INIT_VIDEO
            | SDL_INIT_AUDIO
            | SDL_INIT_EVENTS);

    SDL_Window *p_SDL_window = 
        SDL_CreateWindow(
            "AncientsGame", 0, 0, 800, 600, 
            SDL_WINDOW_OPENGL
            | SDL_WINDOW_SHOWN);

    initialize_sdl_events();

    SDL_establish_scenes(
            get_p_scene_manager_from__game(p_game));

    int exit_code = 
        run_game(p_game);

    SDL_DestroyWindow(p_SDL_window);
    SDL_Quit();

    return exit_code;
}
