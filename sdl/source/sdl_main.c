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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);  

    SDL_Window *p_SDL_window = 
        SDL_CreateWindow(
            "AncientsGame", 0, 0, 800, 600, 
            SDL_WINDOW_OPENGL
            | SDL_WINDOW_SHOWN);

    SDL_GLContext GL_context = SDL_GL_CreateContext(p_SDL_window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        debug_error("SDL::PLATFORM_main failed to load GL functions.");
        return -1;
    }
    
    GL_debug_init();
    initialize_sdl_events();

    SDL_initialize_input_bindings();

    p_game->p_PLATFORM_gfx_context =
        &__SDL_Gfx_Context;
    SDL_initialize_gfx_context(
            get_p_PLATFORM_gfx_context_from__game(p_game), 
            p_SDL_window);
    SDL_SetRenderDrawColor(
            get_p_PLATFORM_gfx_context_from__game(p_game)
            ->p_SDL_renderer,
            0, 0, 0,
            255);

    SDL_establish_scenes(
            get_p_scene_manager_from__game(p_game));

    int exit_code = 
        run_game(p_game);

    SDL_GL_DeleteContext(GL_context);
    SDL_DestroyWindow(p_SDL_window);
    SDL_Quit();

    return exit_code;
}
