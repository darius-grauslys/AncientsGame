#include <entity/entity.h>
#include <rendering/animate_sprite.h>
#include <debug/debug.h>
#include <nds.h>

void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *sprite_wrapper) {
    uint32_t frame =
        sprite_wrapper->frame;
    dmaCopy(sprite_wrapper->sprite.gfx_sprite_sheet +
            (SPRITE_FRAME__16x16__OFFSET
             * frame / 2), sprite_wrapper->sprite.sprite_texture.gfx,
            (SPRITE_FRAME__16x16__OFFSET));
}
