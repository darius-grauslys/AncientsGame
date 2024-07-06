#ifndef NDS_SPRITE_H
#define NDS_SPRITE_H

#include "defines_weak.h"
#include <rendering/sprite.h>
#include <nds_defines.h>

static inline
void NDS_initialize_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Flags sprite_flags) {
    p_PLATFORM_sprite->sprite_flags = sprite_flags;
}

void NDS_set_sprite_graphics_to__item_kind(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Item_Kind the_kind_of__item);

void NDS_update__sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);

static inline
bool NDS_is_sprite__allocated(PLATFORM_Sprite *p_PLATFORM_sprite) {
    return is_sprite_flags__allocated(p_PLATFORM_sprite->sprite_flags);
}

static inline
void NDS_set_sprite_as__allocated(PLATFORM_Sprite *p_PLATFORM_sprite) {
    set_sprite_flags_as__allocated(
            &p_PLATFORM_sprite->sprite_flags);
}

static inline
void NDS_set_sprite_as__deallocated(PLATFORM_Sprite *p_PLATFORM_sprite) {
    set_sprite_flags_as__deallocated(
            &p_PLATFORM_sprite->sprite_flags);
}

static inline
PLATFORM_Sprite *NDS_allocate_sprite_for__entity_on__oam_main(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Entity_Kind the_kind_of__entity) {
    return allocate_sprite_for__entity(
            p_PLATFORM_gfx_context, 
            &p_PLATFORM_gfx_context
                ->graphics_window__main, 
            the_kind_of__entity);
}

static inline
PLATFORM_Sprite *NDS_allocate_sprite_for__entity_on__oam_sub(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Entity_Kind the_kind_of__entity) {
    return allocate_sprite_for__entity(
            p_PLATFORM_gfx_context, 
            &p_PLATFORM_gfx_context
                ->graphics_window__sub, 
            the_kind_of__entity);
}

static inline
PLATFORM_Sprite *NDS_allocate_sprite_for__item_on__oam_main(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Item_Kind the_kind_of__item) {
    return allocate_sprite_for__item(
            p_PLATFORM_gfx_context, 
            &p_PLATFORM_gfx_context
                ->graphics_window__main, 
            the_kind_of__item);
}

static inline
PLATFORM_Sprite *NDS_allocate_sprite_for__item_on__oam_sub(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum Item_Kind the_kind_of__item) {
    return allocate_sprite_for__item(
            p_PLATFORM_gfx_context, 
            &p_PLATFORM_gfx_context
                ->graphics_window__sub, 
            the_kind_of__item);
}

static inline
PLATFORM_Sprite *NDS_allocate_sprite_for__ui(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        enum UI_Sprite_Kind the_kind_of__ui_sprite) {
    return allocate_sprite_for__ui(
            p_PLATFORM_gfx_context, 
            &p_PLATFORM_gfx_context
                ->graphics_window__sub, 
            the_kind_of__ui_sprite);
}

static inline
u8 *NDS_get_p_gfx_offset_with__8x8_as__p_u8(
        void *p_gfx, Quantity__u32 offset,
        Quantity__u32 quantity_of__frame_offsets) {
    return ((u8*)p_gfx
            + (SPRITE_FRAME__8x8__OFFSET
            * quantity_of__frame_offsets));
}

static inline
u8 *NDS_get_p_gfx_offset_with__16x16_as__p_u8(
        void *p_gfx, Quantity__u32 offset,
        Quantity__u32 quantity_of__frame_offsets) {
    return ((u8*)p_gfx
            + (SPRITE_FRAME__16x16__OFFSET
            * quantity_of__frame_offsets));
}

static inline
u8 *NDS_get_p_gfx_offset_with__32x32_as__p_u8(
        void *p_gfx, Quantity__u32 offset,
        Quantity__u32 quantity_of__frame_offsets) {
    return ((u8*)p_gfx
            + (SPRITE_FRAME__32x32__OFFSET
            * quantity_of__frame_offsets));
}

#endif
