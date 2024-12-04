#ifndef SDL_BACKGROUND_H
#define SDL_BACKGROUND_H

#include "defines_weak.h"
#include "sdl_defines.h"

typedef enum SDL_Background_Kind {
    SDL_Background_Kind__None = 0,
    SDL_Background_Kind__Inventory_Column = 1,
    SDL_Background_Kind__Inventory_Column__Small,
    SDL_Background_Kind__Equipment,
    SDL_Background_Kind__Equipment_Divider,
    SDL_Background_Kind__Unknown
} SDL_Background_Kind;

PLATFORM_Graphics_Window *SDL_allocate_background_as__PLATFORM_Gfx_Window(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window__parent,
        SDL_Background_Kind the_kind_of__background,
        Vector__3i32 origin_of__window);

#endif
