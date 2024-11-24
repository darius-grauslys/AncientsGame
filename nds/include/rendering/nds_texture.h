#ifndef NDS_TEXTURE_H
#define NDS_TEXTURE_H

#include "defines.h"
#include "defines_weak.h"
#include <nds_defines.h>

///
/// This does NOT allocate memory.
///
void NDS_initialize_texture(
        PLATFORM_Texture *p_PLATFORM_texture,
        OamState *oam,
        uint16_t *gfx,
        uint16_t *gfx__readonly,
        uint32_t oam_index,
        Texture_Flags texture_flags,
        uint8_t dma_channel,
        enum NDS_Texture_Kind the_kind_of__texture);

void NDS_update_texture_for__oam(
        PLATFORM_Texture *p_texture,
        Index__u8 palette,
        SpriteColorFormat color_format_for__sprite);

void NDS_allocate_texture(
        PLATFORM_Texture *p_texture, 
        Texture_Allocation_Specification
            *p_texture_allocation_specification);

static inline
void NDS_initialize_texture_as__deallocated(
        PLATFORM_Texture *p_PLATFORM_texture) {
    NDS_initialize_texture(
            p_PLATFORM_texture,
            0,
            0,
            0,
            0,
            TEXTURE_FLAGS__NONE,
            0,
            NDS_Texture_Kind__None
            );
}

static inline
Texture_Flags *NDS_get_p_texture_flags_from__PLATFORM_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return &p_PLATFORM_texture->flags;
}

static inline
bool NDS_is_texture_of__this_texture_kind(
        PLATFORM_Texture *p_PLATFORM_texture,
        enum NDS_Texture_Kind the_kind_of__texture) {
    return the_kind_of__texture
        == p_PLATFORM_texture->the_kind_of__texture;
}

static inline
uint16_t *NDS_get_p_gfx_from__PLATFORM_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return p_PLATFORM_texture->gfx;
}

static inline
uint8_t NDS_get_dma_channel_from__PLATFORM_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return p_PLATFORM_texture->dma_channel;
}

static inline
void NDS_wait_for_dma_channel_of__PLATFORM_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    uint8_t dma_channel =
        NDS_get_dma_channel_from__PLATFORM_texture(
                p_PLATFORM_texture);
    while (DMA_CR(dma_channel) & DMA_BUSY);
}

static inline
OamState *NDS_get_oam_from__PLATFORM_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return p_PLATFORM_texture->oam;
}

static inline
uint32_t NDS_get_oam_index_of__PLATFORM_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return p_PLATFORM_texture
        ->oam_index;
}

#endif
