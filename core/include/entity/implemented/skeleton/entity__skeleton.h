#ifndef ENTITY__SKELETON_H
#define ENTITY__SKELETON_H

#include "defines_weak.h"
#include <defines.h>

void initialize_entity_as__skeleton(
        Game *p_game,
        Graphics_Window
            *p_graphics_window,
        Entity *p_entity,
        Vector__3i32F4 position__3i32F4);

bool f_sprite_gfx_allocator__skeleton(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        Sprite_Wrapper *p_sprite_wrapper,
        u32 enum_value);

#endif
