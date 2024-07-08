#ifndef NDS_TEXTURE_H
#define NDS_TEXTURE_H

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

void NDS_initialize_texture_as__empty(
        PLATFORM_Texture *p_PLATFORM_texture);

void NDS_update_texture_for__oam(
        PLATFORM_Texture *p_texture,
        Index__u8 palette,
        SpriteColorFormat color_format_for__sprite);

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


#endif
