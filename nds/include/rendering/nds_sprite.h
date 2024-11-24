#ifndef NDS_SPRITE_H
#define NDS_SPRITE_H

#include "defines_weak.h"
#include "nds_texture.h"
#include <rendering/sprite.h>
#include <nds_defines.h>

void NDS_initialize_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Flags sprite_flags);

void NDS_set_sprite_graphics_to__item_kind(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Item_Kind the_kind_of__item);

void NDS_update__sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);

void NDS_set_sprite__texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfX_context,
        PLATFORM_Sprite *p_PLATFORM_sprite,
        PLATFORM_Texture *p_PLATFORM_texture);

static inline
Sprite_Flags *NDS_get_p_sprite_flags_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return &p_PLATFORM_sprite
        ->sprite_flags;
}

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

static inline
PLATFORM_Texture *NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return p_PLATFORM_sprite
        ->p_PLATFORM_texture__sprite
        ;
}

static inline
SpriteSize NDS_get_sprite_size_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return p_PLATFORM_sprite
        ->p_PLATFORM_texture__sprite
        ->sprite_size
        ;
}

static inline
Texture_Flags *NDS_get_p_texture_flags_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return
        PLATFORM_get_p_texture_flags_from__PLATFORM_texture(
                NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                    p_PLATFORM_sprite));
}

static inline
uint16_t *NDS_get_p_gfx_from__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return NDS_get_p_gfx_from__PLATFORM_texture(
            NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite));
}

static inline
uint8_t NDS_get_dma_channel_from__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return NDS_get_dma_channel_from__PLATFORM_texture(
            NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite));
}

static inline
void NDS_wait_for_dma_channel_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    NDS_wait_for_dma_channel_of__PLATFORM_texture(
            NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite));
}

static inline
OamState *NDS_get_oam_from__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return NDS_get_oam_from__PLATFORM_texture(
            NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite));
}

static inline
uint32_t NDS_get_oam_index_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return NDS_get_oam_index_of__PLATFORM_texture(
            NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite));
}

static inline
bool NDS_is_sprite_texture__allocated(
        PLATFORM_Sprite *p_PLATORM_sprite) {
    return is_texture_flags__allocated(
            *NDS_get_p_texture_flags_of__PLATFORM_sprite(
                p_PLATORM_sprite));
}

static inline
void NDS_set_position_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Quantity__u32 x,
        Quantity__u32 y) {
    oamSetXY(
            NDS_get_oam_from__PLATFORM_sprite(
                p_PLATFORM_sprite),
            NDS_get_oam_index_of__PLATFORM_sprite(
                p_PLATFORM_sprite),
            x, y);
}

static inline
void NDS_set_hidden__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        bool state_of__hidden) {
    oamSetHidden(
            NDS_get_oam_from__PLATFORM_sprite(
                p_PLATFORM_sprite),
            NDS_get_oam_index_of__PLATFORM_sprite(
                p_PLATFORM_sprite),
            state_of__hidden);
}

static inline
void NDS_set_flip_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        bool flip_vertical,
        bool flip_horizontal) {
    oamSetFlip(
            NDS_get_oam_from__PLATFORM_sprite(
                p_PLATFORM_sprite),
            NDS_get_oam_index_of__PLATFORM_sprite(
                p_PLATFORM_sprite),
            flip_vertical,
            flip_horizontal);
}

static inline
void NDS_set_priority_of__PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Index__u8 priority) {
    oamSetPriority(
            NDS_get_oam_from__PLATFORM_sprite(
                p_PLATFORM_sprite),
            NDS_get_oam_index_of__PLATFORM_sprite(
                p_PLATFORM_sprite),
            priority);
}

#endif
