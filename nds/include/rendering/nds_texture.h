#ifndef NDS_TEXTURE_H
#define NDS_TEXTURE_H

#include <nds_defines.h>

void NDS_update_texture_for__oam(
        PLATFORM_Texture *p_texture,
        Index__u8 palette,
        SpriteColorFormat color_format_for__sprite);

#endif
