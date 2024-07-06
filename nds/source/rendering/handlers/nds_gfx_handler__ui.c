#include "defines_weak.h"
#include <nds_defines.h>
#include <rendering/handlers/nds_gfx_handler__ui.h>

#include <assets/ui/sprites/ui_sprite__8x8/ui_sprites__8x8.h>
#include <assets/ui/sprites/ui_sprite__16x16/ui_sprites__16x16.h>
#include <assets/ui/sprites/ui_sprite__32x32/ui_sprites__32x32.h>

void f_sprite_gfx_allocator__handler_for__ui(
        PLATFORM_Sprite *p_PLATFORM_sprite, 
        Sprite_Allocation_Specification
            *p_sprite_allocation_specification) {
    enum UI_Sprite_Kind the_kind_of__ui_sprite =
        p_sprite_allocation_specification
        ->the_kind_of__ui__this_sprite_is;

    Texture_Flags *p_texture_flags =
        &p_sprite_allocation_specification
            ->texture_allocation_specification
            .texture_flags;

    if (UI_Sprite_Kind__8x8 >
            the_kind_of__ui_sprite) {
        *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
        *p_texture_flags |= TEXTURE_FLAG__SIZE_8x8;

        PLATFORM_allocate_texture(
                &p_PLATFORM_sprite->sprite_texture,
                &p_sprite_allocation_specification
                    ->texture_allocation_specification);

        dmaCopy((u8*)(ui_sprites__8x8Tiles)
                + (SPRITE_FRAME__8x8__OFFSET
                * (Index__u32)the_kind_of__ui_sprite),
                p_PLATFORM_sprite->sprite_texture.gfx, 
                SPRITE_FRAME__8x8__OFFSET);

        PLATFORM_update_sprite(p_PLATFORM_sprite);
        return;
    }

    if (UI_Sprite_Kind__16x16 >
            the_kind_of__ui_sprite) {
        *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
        *p_texture_flags |= TEXTURE_FLAG__SIZE_16x16;

        the_kind_of__ui_sprite -=
            UI_Sprite_Kind__8x8;

        PLATFORM_allocate_texture(
                &p_PLATFORM_sprite->sprite_texture,
                &p_sprite_allocation_specification
                    ->texture_allocation_specification);

        dmaCopy((u8*)(ui_sprites__16x16Tiles)
                + (SPRITE_FRAME__16x16__OFFSET
                * (Index__u32)the_kind_of__ui_sprite),
                p_PLATFORM_sprite->sprite_texture.gfx, 
                SPRITE_FRAME__16x16__OFFSET);

        PLATFORM_update_sprite(p_PLATFORM_sprite);
        return;
    }

    *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
    *p_texture_flags |= TEXTURE_FLAG__SIZE_32x32;

    the_kind_of__ui_sprite -=
        UI_Sprite_Kind__16x16;

    PLATFORM_allocate_texture(
            &p_PLATFORM_sprite->sprite_texture,
            &p_sprite_allocation_specification
                ->texture_allocation_specification);

    dmaCopy((u8*)(ui_sprites__32x32Tiles)
            + (SPRITE_FRAME__32x32__OFFSET
            * (Index__u32)the_kind_of__ui_sprite),
            p_PLATFORM_sprite->sprite_texture.gfx, 
            SPRITE_FRAME__32x32__OFFSET);

    PLATFORM_update_sprite(p_PLATFORM_sprite);
}
