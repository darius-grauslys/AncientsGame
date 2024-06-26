#ifndef NDS_SPRITE_H
#define NDS_SPRITE_H

#include "defines_weak.h"
#include <nds_defines.h>

static inline
void NDS_initialize_sprite_pallete(
        NDS_Sprite_Pallete *p_NDS_sprite_pallete,
        const uint16_t *p_sprite_pallete,
        Index__u8 pallete_slot,
        Quantity__u32 pallete_length) {
    p_NDS_sprite_pallete->p_pallete =
        p_sprite_pallete;
    p_NDS_sprite_pallete->pallete_slot =
        pallete_slot;
    p_NDS_sprite_pallete->pallete_length =
        pallete_length;
}

void NDS_update__sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite);

#endif
