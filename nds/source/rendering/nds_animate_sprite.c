#include <entity/entity.h>
#include <rendering/animate_sprite.h>
#include <debug/debug.h>
#include <nds.h>

void PLATFORM_update_sprite_gfx__to_current_frame(Entity *entity) {
    uint32_t frame =
        entity->sprite_wrapper.frame;
    dmaCopy(entity->sprite_wrapper.sprite.gfx_sprite_sheet +
            (SPRITE_FRAME_WIDTH__ENTITY_HUMANOID 
             * SPRITE_FRAME_HEIGHT__ENTITY_HUMANOID
             * frame / 2), entity->sprite_wrapper.sprite.sprite_texture.gfx,
            (SPRITE_FRAME_WIDTH__ENTITY_HUMANOID *
             SPRITE_FRAME_HEIGHT__ENTITY_HUMANOID));
}
