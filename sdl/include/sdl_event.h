#ifndef SDL_EVENT_H
#define SDL_EVENT_H

#include "platform.h"
#include "platform_defines.h"
#include <SDL2/SDL_events.h>

void poll_sdl_event(Game *p_game);

void initialize_sdl_events();

void register_sdl_event(
        SDL_EventType the_kind_of__sdl_event,
        f_SDL_Event_Handler f_sdl_event_handler);

#endif
