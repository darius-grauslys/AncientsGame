#include "defines.h"
#include "defines_weak.h"
#include "nds/arm9/sprite.h"
#include "platform_defines.h"
#include <rendering/sprite.h>
#include <rendering/nds_sprite.h>
#include <rendering/texture.h>
#include <entity/entity.h>
#include <nds.h>
#include <debug/debug.h>

#include <assets/entities/entity_sprite__16x16/zombie.h>
#include <assets/entities/entity_sprite__8x8/items.h>

#include <stdint.h>
#include <nds_defines.h>

/// no-op
void PLATFORM_render_sprite(Sprite_Wrapper *sprite_wrapper) { }

void PLATFORM_update_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    uint8_t palette = 0;
    switch (p_PLATFORM_sprite->sprite_texture.sprite_size) {
        default:
        case SpriteSize_8x8:
            break;
        case SpriteSize_16x16:
            palette = 1;
            break;
    }
    oamSet(
            p_PLATFORM_sprite->sprite_texture.oam, 
            p_PLATFORM_sprite->sprite_texture.oam_index, 
            127 - 8, 96 - 8, 
            1, 
            palette,
            p_PLATFORM_sprite->sprite_texture
                .sprite_size, 
            SpriteColorFormat_256Color, 
            p_PLATFORM_sprite->sprite_texture.gfx, 
            -1, 
            false, 
            false, 
            false, false, 
            false);
}

void PLATFORM_set_sprite__position(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Index__u16 x, Index__u16 y) {
    oamSetXY(
            p_PLATFORM_sprite->sprite_texture.oam,
            p_PLATFORM_sprite->sprite_texture.oam_index,
            x - (p_PLATFORM_sprite->sprite_texture.width >> 1), 
            y - (p_PLATFORM_sprite->sprite_texture.height >> 1));
}

Sprite_Flags *PLATFORM_get_p_sprite_flags__from_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return &p_PLATFORM_sprite->sprite_flags;
}
