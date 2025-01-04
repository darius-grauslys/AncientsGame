#ifndef ENTITY__SKELETON_H
#define ENTITY__SKELETON_H

#include <defines.h>

void initialize_entity_as__skeleton(
        Game *p_game,
        PLATFORM_Graphics_Window
            *p_PLATFORM_graphics_window,
        Entity *p_entity,
        Vector__3i32F4 position__3i32F4);

bool f_sprite_gfx_allocator__skeleton(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        Sprite_Wrapper *p_sprite_wrapper,
        u32 enum_value);

#endif
