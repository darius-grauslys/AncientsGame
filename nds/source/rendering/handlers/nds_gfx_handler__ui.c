#include "defines_weak.h"
#include <nds_defines.h>
#include <rendering/handlers/nds_gfx_handler__ui.h>

#include <assets/ui/sprites/ui_sprite__8x8/ui_sprites__8x8.h>
#include <assets/ui/sprites/ui_sprite__16x16/ui_sprites__16x16.h>
#include <assets/ui/sprites/ui_sprite__32x32/ui_sprites__32x32.h>
#include "rendering/nds_sprite.h"

void f_sprite_gfx_allocator__handler_for__ui(
        PLATFORM_Gfx_Context *p_PLATFORM_gfx_context,
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

    u8* p_gfx_source = 0;
    uint offset = SPRITE_FRAME__8x8__OFFSET;

    if (UI_Sprite_Kind__8x8 >
            the_kind_of__ui_sprite) {
        *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
        *p_texture_flags |= TEXTURE_FLAG__SIZE_8x8;

        offset = SPRITE_FRAME__8x8__OFFSET;

        p_gfx_source =
            (u8*)(ui_sprites__8x8Tiles)
            + (SPRITE_FRAME__8x8__OFFSET
            * (Index__u32)the_kind_of__ui_sprite)
            ;
    } else if (UI_Sprite_Kind__16x16 >
            the_kind_of__ui_sprite) {
        the_kind_of__ui_sprite -=
            UI_Sprite_Kind__8x8;

        *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
        *p_texture_flags |= TEXTURE_FLAG__SIZE_16x16;

        offset = SPRITE_FRAME__16x16__OFFSET;

        p_gfx_source =
            (u8*)(ui_sprites__16x16Tiles)
            + (SPRITE_FRAME__16x16__OFFSET
            * (Index__u32)the_kind_of__ui_sprite)
            ;
    } else {
        the_kind_of__ui_sprite -=
            UI_Sprite_Kind__16x16;

        *p_texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
        *p_texture_flags |= TEXTURE_FLAG__SIZE_32x32;

        offset = SPRITE_FRAME__32x32__OFFSET;

        p_gfx_source =
            (u8*)(ui_sprites__32x32Tiles)
            + (SPRITE_FRAME__32x32__OFFSET
            * (Index__u32)the_kind_of__ui_sprite)
            ;
    }

    PLATFORM_Texture *p_PLATFORM_texture =
        PLATFORM_allocate_texture(
                p_PLATFORM_gfx_context,
                &p_sprite_allocation_specification
                    ->texture_allocation_specification);

    NDS_set_sprite__texture(
            p_PLATFORM_gfx_context, 
            p_PLATFORM_sprite, 
            p_PLATFORM_texture);

    dmaCopy(p_gfx_source,
            NDS_get_p_gfx_from__PLATFORM_sprite(
                p_PLATFORM_sprite), 
            offset);

    PLATFORM_update_sprite(p_PLATFORM_sprite);
}
