#include "platform.h"
#include <nds_defines.h>
#include <rendering/handlers/nds_gfx_handler__player.h>
#include <assets/entities/entity_sprite__16x16/player.h>
#include "rendering/nds_sprite.h"

void f_sprite_gfx_allocator__handler_for__player(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    Texture_Flags *p_texture_flags =
        &p_sprite_allocation_specification
        ->texture_allocation_specification
        .texture_flags;
    *p_texture_flags &= TEXTURE_FLAG__SIZE__MASK;
    *p_texture_flags |= TEXTURE_FLAG__SIZE_16x16;

    PLATFORM_Texture *p_PLATFORM_texture =
        PLATFORM_allocate_texture(
                p_PLATFORM_gfx_context,
                &p_sprite_allocation_specification
                    ->texture_allocation_specification);

    NDS_set_sprite__texture(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_sprite, 
            p_PLATFORM_texture);

    p_PLATFORM_sprite
        ->gfx_sprite_sheet = (const uint16_t*)playerTiles;

    dmaCopy((u8*)playerTiles, 
            NDS_get_p_gfx_from__PLATFORM_sprite(
                p_PLATFORM_sprite), 
            SPRITE_FRAME__16x16__OFFSET);
}
