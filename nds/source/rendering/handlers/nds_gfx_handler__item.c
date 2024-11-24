#include "defines_weak.h"
#include "platform.h"
#include "rendering/sprite.h"
#include "rendering/nds_sprite.h"
#include <nds_defines.h>
#include <rendering/handlers/nds_gfx_handler__item.h>
#include <assets/entities/entity_sprite__8x8/items.h>

void f_sprite_gfx_allocator__handler_for__items(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
        PLATFORM_Sprite *p_PLATFORM_sprite, 
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    Texture_Flags *p_texture_flags =
        &p_sprite_allocation_specification
            ->texture_allocation_specification
            .texture_flags;
    *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
    *p_texture_flags |= TEXTURE_FLAG__SIZE_8x8;

    PLATFORM_Texture *p_PLATFORM_texture =
        PLATFORM_allocate_texture(
                p_PLATFORM_gfx_context,
                &p_sprite_allocation_specification
                    ->texture_allocation_specification);

    NDS_set_sprite__texture(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_sprite, 
            p_PLATFORM_texture);

    NDS_set_sprite_graphics_to__item_kind(
            p_PLATFORM_sprite,
            p_sprite_allocation_specification
                ->the_kind_of__item_this__sprite_is);

    PLATFORM_update_sprite(p_PLATFORM_sprite);
}

void NDS_set_sprite_graphics_to__item_kind(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Item_Kind the_kind_of__item) {
    NDS_wait_for_dma_channel_of__PLATFORM_sprite(p_PLATFORM_sprite);
    // TODO: support 16x16, 32x32
    dmaCopy(
            NDS_get_p_gfx_of__item_sprite_as__p_u8(
                the_kind_of__item),
            NDS_get_p_gfx_from__PLATFORM_sprite(p_PLATFORM_sprite), 
            SPRITE_FRAME__8x8__OFFSET);
}

u8 *NDS_get_p_gfx_of__item_sprite_as__p_u8(
        enum Item_Kind the_kind_of__item) {
    return (u8*)(itemsTiles)
            + (SPRITE_FRAME__8x8__OFFSET
            * (Index__u32)the_kind_of__item)
            ;
}
