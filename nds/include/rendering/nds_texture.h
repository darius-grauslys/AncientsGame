#ifndef NDS_TEXTURE_H
#define NDS_TEXTURE_H

#include "defines_weak.h"
#include <nds_defines.h>

void NDS_update_texture_for__oam(
        PLATFORM_Texture *p_texture,
        Index__u8 palette,
        SpriteColorFormat color_format_for__sprite);

static inline
Texture_Flags *NDS_get_p_texture_flags_from__PLATFORM_texture(
        PLATFORM_Texture *p_PLATFORM_texture) {
    return &p_PLATFORM_texture->flags;
}

#endif
