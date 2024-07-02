#include "defines_weak.h"
#include "platform.h"
#include "rendering/sprite.h"
#include "rendering/nds_sprite.h"
#include <nds_defines.h>
#include <rendering/handlers/nds_gfx_handler__item.h>
#include <assets/entities/entity_sprite__8x8/items.h>

void f_sprite_gfx_allocator__handler_for__items(
        PLATFORM_Sprite *p_PLATFORM_sprite, 
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    Texture_Flags *p_texture_flags =
        &p_sprite_allocation_specification
            ->texture_allocation_specification
            .texture_flags;
    *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
    *p_texture_flags |= TEXTURE_FLAG__SIZE_8x8;

    PLATFORM_allocate_texture(
            &p_PLATFORM_sprite->sprite_texture,
            &p_sprite_allocation_specification
                ->texture_allocation_specification);

    NDS_set_sprite_graphics_to__item_kind(
            p_PLATFORM_sprite,
            p_sprite_allocation_specification
                ->the_kind_of__item_this__sprite_is);

    PLATFORM_update_sprite(p_PLATFORM_sprite);
}
