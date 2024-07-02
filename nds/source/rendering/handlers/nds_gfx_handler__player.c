#include "platform.h"
#include <nds_defines.h>
#include <rendering/handlers/nds_gfx_handler__player.h>
#include <assets/entities/entity_sprite__16x16/player.h>

void f_sprite_gfx_allocator__handler_for__player(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    Texture_Flags *p_texture_flags =
        &p_sprite_allocation_specification
        ->texture_allocation_specification
        .texture_flags;
    *p_texture_flags &= TEXTURE_FLAG__SIZE__MASK;
    *p_texture_flags |= TEXTURE_FLAG__SIZE_16x16;
    PLATFORM_allocate_texture(
            &p_PLATFORM_sprite->sprite_texture,
            &p_sprite_allocation_specification
                ->texture_allocation_specification);
    p_PLATFORM_sprite
        ->gfx_sprite_sheet = (const uint16_t*)playerTiles;
    dmaCopy((u8*)playerTiles, 
            p_PLATFORM_sprite->sprite_texture.gfx, 
            SPRITE_FRAME__16x16__OFFSET);
}
