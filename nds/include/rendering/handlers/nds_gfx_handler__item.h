#ifndef NDS_GFX_HANDLER__ITEM_H
#define NDS_GFX_HANDLER__ITEM_H

#include <defines_weak.h>

void f_sprite_gfx_allocator__handler_for__items(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite, 
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification);

void NDS_set_sprite_graphics_to__item_kind(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Item_Kind the_kind_of__item);

u8 *NDS_get_p_gfx_of__item_sprite_as__p_u8(
        enum Item_Kind the_kind_of__item);

#endif
