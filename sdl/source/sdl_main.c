#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <platform.h>
#include <SDL2/SDL.h>

int PLATFORM_main(Game *game) {
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
    while(true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)
                && event.type == SDL_QUIT) {
            break;
        }
    }
    SDL_DestroyWindow(p_SDL_window);
    SDL_Quit();
    return 0;
}
