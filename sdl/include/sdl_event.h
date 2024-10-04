#ifndef SDL_EVENT_H
#define SDL_EVENT_H

#include "platform.h"
#include "platform_defines.h"
#include <SDL2/SDL_events.h>

void SDL_poll_event(Game *p_game);

void SDL_initialize_events();

void f_SDL_event_handler__resize(
        Game *p_game,
        SDL_Event *p_event);

void SDL_register_event(
        SDL_EventType the_kind_of__sdl_event,
        f_SDL_Event_Handler f_sdl_event_handler);

void SDL_register_window_event(
        SDL_WindowEventID the_kind_of__window_event,
        f_SDL_Event_Handler f_sdl_event_handler);

#endif
