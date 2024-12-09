#include "defines_weak.h"
#include "game.h"
#include "platform_defines.h"
#include "scene/scene_manager.h"
#include <SDL2/SDL_events.h>
#include <sdl_event.h>
#include <sdl_defines.h>

f_SDL_Event_Handler __SDL_EVENT_HANDLERS[SDL_LASTEVENT] = {0};
f_SDL_Event_Handler __SDL_EVENT_WINDOW_HANDLERS[SDL_WINDOWEVENT_DISPLAY_CHANGED] = {0};

void SDL_poll_event(Game *p_game) {
    SDL_Event event;
    if (!SDL_PollEvent(&event))
        return;

    if (__SDL_EVENT_HANDLERS[event.type]) {
        __SDL_EVENT_HANDLERS[event.type](
                p_game,
                &event);
    }
}

void f_SDL_event_handler__quit(
        Game *p_game,
        SDL_Event *p_event) {
    quit_scene_state_machine(
            get_p_scene_manager_from__game(p_game));
}

void f_SDL_event_handler__resize(
        Game *p_game,
        SDL_Event *p_event) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    SDL_GetWindowSize(
            p_PLATFORM_gfx_context
            ->p_SDL_window, 
            &p_PLATFORM_gfx_context->width_of__sdl_window, 
            &p_PLATFORM_gfx_context->height_of__sdl_window);
}

void f_SDL_event_handler__window(
        Game *p_game,
        SDL_Event *p_event) {
    f_SDL_Event_Handler f_SDL_event_handler =
        __SDL_EVENT_WINDOW_HANDLERS[
            p_event->window.event];
    if (f_SDL_event_handler) {
        f_SDL_event_handler(
                p_game,
                p_event);
    }
}


void SDL_initialize_events() {
    SDL_register_event(
            SDL_QUIT, 
            f_SDL_event_handler__quit);
    SDL_register_event(
            SDL_WINDOWEVENT,
            f_SDL_event_handler__window);
    SDL_register_window_event(
            SDL_WINDOWEVENT_RESIZED, 
            f_SDL_event_handler__resize);
}

void SDL_register_event(
        SDL_EventType the_kind_of__sdl_event,
        f_SDL_Event_Handler f_sdl_event_handler) {
    __SDL_EVENT_HANDLERS[
        (u16)the_kind_of__sdl_event] =
            f_sdl_event_handler;
}

void SDL_register_window_event(
        SDL_WindowEventID the_kind_of__sdl_event,
        f_SDL_Event_Handler f_sdl_event_handler) {
    __SDL_EVENT_WINDOW_HANDLERS[
        (u16)the_kind_of__sdl_event] =
            f_sdl_event_handler;
}
