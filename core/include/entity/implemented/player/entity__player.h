#ifndef ENTITY__PLAYER_H
#define ENTITY__PLAYER_H

#include <defines.h>

void initialize_entity_as__player(
        Game *p_game,
        PLATFORM_Graphics_Window
            *p_PLATFORM_graphics_window,
        Entity *p_entity,
        Vector__3i32F4 position__3i32F4);

PLATFORM_Sprite *f_sprite_gfx_allocator__player(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        u32 enum_value);

#endif
