#include "game.h"
#include "platform_defines.h"
#include "scene/scene_manager.h"
#include <SDL2/SDL_events.h>
#include <sdl_event.h>

f_SDL_Event_Handler __SDL_EVENT_HANDLERS[SDL_LASTEVENT] = {0};

void SDL_poll_event(Game *p_game) {
    SDL_Event event;
    if (!SDL_PollEvent(&event))
        return;

    if (__SDL_EVENT_HANDLERS[event.type])
        __SDL_EVENT_HANDLERS[event.type](p_game);
}

void f_SDL_event_handler__quit(
        Game *p_game) {
    quit_scene_state_machine(
            get_p_scene_manager_from__game(p_game));
}

void SDL_initialize_events() {
    SDL_register_event(
            SDL_QUIT, 
            f_SDL_event_handler__quit);
}

void SDL_register_event(
        SDL_EventType the_kind_of__sdl_event,
        f_SDL_Event_Handler f_sdl_event_handler) {
    __SDL_EVENT_HANDLERS[
        (u16)the_kind_of__sdl_event] =
            f_sdl_event_handler;
}
