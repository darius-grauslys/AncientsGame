#include <entity/entity.h>
#include <rendering/animate_sprite.h>
#include <debug/debug.h>
#include <nds.h>
#include <nds_defines.h>

void PLATFORM_update_sprite_gfx__to_current_frame(
        Sprite_Wrapper *p_sprite_wrapper) {
    uint32_t frame =
        p_sprite_wrapper->frame;
    dmaCopy(p_sprite_wrapper->p_sprite->gfx_sprite_sheet +
            (SPRITE_FRAME__16x16__OFFSET
             * frame / 2), p_sprite_wrapper->p_sprite->sprite_texture.gfx,
            (SPRITE_FRAME__16x16__OFFSET));
}
