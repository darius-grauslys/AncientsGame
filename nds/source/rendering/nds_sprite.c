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
#include "rendering/nds_texture.h"

#include <assets/entities/entity_sprite__16x16/zombie.h>
#include <assets/entities/entity_sprite__8x8/items.h>

#include <stdint.h>
#include <nds_defines.h>

void NDS_initialize_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Flags sprite_flags) {
    NDS_initialize_texture_as__deallocated(
            NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite));
    p_PLATFORM_sprite->sprite_flags = sprite_flags;
}

/// no-op
void PLATFORM_render_sprite(Sprite_Wrapper *sprite_wrapper) { }

void PLATFORM_update_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    uint8_t palette = 0;
    switch (NDS_get_sprite_size_of__PLATFORM_sprite(
                p_PLATFORM_sprite)) {
        default:
        case SpriteSize_8x8:
            break;
        case SpriteSize_16x16:
            palette = 1;
            break;
    }
    PLATFORM_Texture *p_PLATFORM_texture =
        NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite);
    oamSet(
            p_PLATFORM_texture->oam, 
            p_PLATFORM_texture->oam_index, 
            127 - 8, 96 - 8, 
            1, 
            palette,
            NDS_get_sprite_size_of__PLATFORM_sprite(
                p_PLATFORM_sprite),
            SpriteColorFormat_256Color, 
            p_PLATFORM_texture->gfx, 
            -1, 
            false, 
            false, 
            false, false, 
            false);
}

void PLATFORM_set_sprite__position(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Index__u16 x, Index__u16 y) {
    PLATFORM_Texture *p_PLATFORM_texture =
        NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite);
    oamSetXY(
            p_PLATFORM_texture->oam,
            p_PLATFORM_texture->oam_index,
            x - (p_PLATFORM_texture->width >> 1), 
            y - (p_PLATFORM_texture->height >> 1));
}

Sprite_Flags *PLATFORM_get_p_sprite_flags__from_PLATFORM_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    return &p_PLATFORM_sprite->sprite_flags;
}

void NDS_set_sprite__texture(
        PLATFORM_Gfx_Context *p_PLATFORM_gfX_context,
        PLATFORM_Sprite *p_PLATFORM_sprite,
        PLATFORM_Texture *p_PLATFORM_texture) {
    PLATFORM_Texture *p_PLATFORM_texture_of__sprite_currently =
        NDS_get_p_PLATFORM_texture_from__PLATFORM_sprite(
                p_PLATFORM_sprite);

    if (p_PLATFORM_texture_of__sprite_currently) {
        PLATFORM_release_texture(
                p_PLATFORM_gfX_context, 
                p_PLATFORM_texture_of__sprite_currently);
    }

    p_PLATFORM_sprite
        ->p_PLATFORM_texture__sprite =
        p_PLATFORM_texture
        ;
}
