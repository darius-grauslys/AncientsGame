#include "defines.h"
#include "defines_weak.h"
#include "nds/arm9/sprite.h"
#include "platform_defines.h"
#include <rendering/sprite.h>
#include <rendering/texture.h>
#include <entity/entity.h>
#include <nds.h>
#include <debug/debug.h>

#include <assets/entities/entity_sprite__16x16/player.h>
#include <assets/entities/entity_sprite__16x16/skeleton.h>
#include <assets/entities/entity_sprite__16x16/zombie.h>

#include <assets/entities/entity_sprite__8x8/items.h>
#include <stdint.h>

/// no-op
void PLATFORM_render_sprite(Sprite_Wrapper *sprite_wrapper) { }

void PLATFORM_initialize_sprite(
        PLATFORM_Sprite *sprite,
        Texture_Flags texture_flags_for__sprite,
        bool perform_update) {
    // TODO: debug_warning("PLATFORM_initialize_sprite is not finished yet:
    //         doesn't support oamSub.");
    while (DMA_CR(sprite->sprite_texture.dma_channel) & DMA_BUSY);
    PLATFORM_allocate_texture(
            &sprite->sprite_texture,
            texture_flags_for__sprite);
}

void PLATFORM_initialize_sprite_for__entity(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Entity_Kind the_kind_of__entity,
        Texture_Flags texture_flags) {
    // drop the size flags
    texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
    texture_flags |= TEXTURE_FLAG__USE_OAM;
    texture_flags |= TEXTURE_FLAG__USE_OAM_MAIN_OR_SUB;
    while (DMA_CR(p_PLATFORM_sprite->sprite_texture.dma_channel) & DMA_BUSY);
    switch(the_kind_of__entity) {
        default:
            debug_abort("Entity_Kind %d not implemented for PLATFORM_initialize_sprite_for__entity.",
                    the_kind_of__entity);
            return;
        case Entity_Kind__Player:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            texture_flags |= TEXTURE_FLAG__SIZE_16x16;
            break;
    }

    PLATFORM_initialize_sprite(
            p_PLATFORM_sprite,
            texture_flags,
            false);

    switch (the_kind_of__entity) {
        default:
            return;
        case Entity_Kind__Player:
            p_PLATFORM_sprite
                ->gfx_sprite_sheet = (const uint16_t*)playerTiles;
            dmaCopy((u8*)playerTiles, 
                    p_PLATFORM_sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            break;
        case Entity_Kind__Skeleton:
            texture_flags |= TEXTURE_FLAG__SIZE_16x16;
            p_PLATFORM_sprite
                ->gfx_sprite_sheet = (const uint16_t*)skeletonTiles;
            dmaCopy((u8*)skeletonTiles, 
                    p_PLATFORM_sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            break;
        case Entity_Kind__Zombie:
            texture_flags |= TEXTURE_FLAG__SIZE_16x16;
            p_PLATFORM_sprite
                ->gfx_sprite_sheet = (const uint16_t*)zombieTiles;
            dmaCopy((u8*)zombieTiles, 
                    p_PLATFORM_sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            break;
    }

    // TODO: move this to texture.
    PLATFORM_update_sprite(p_PLATFORM_sprite);
}

void PLATFORM_initialize_sprite_for__item(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Item_Kind the_kind_of__item,
        Texture_Flags texture_flags) {
    texture_flags &= ~TEXTURE_FLAG__SIZE__MASK;
    texture_flags |= TEXTURE_FLAG__USE_OAM;
    texture_flags |= TEXTURE_FLAG__SIZE_8x8;

    PLATFORM_initialize_sprite(
            p_PLATFORM_sprite,
            texture_flags,
            false);

    PLATFORM_set_sprite_graphics_to__item_kind(
            p_PLATFORM_sprite,
            the_kind_of__item);

    PLATFORM_update_sprite(p_PLATFORM_sprite);
}

void PLATFORM_set_sprite_graphics_to__item_kind(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        enum Item_Kind the_kind_of__item) {
    while (DMA_CR(p_PLATFORM_sprite->sprite_texture.dma_channel) & DMA_BUSY);
    dmaCopy((u8*)(itemsTiles)
            + (SPRITE_FRAME__8x8__OFFSET
            * (Index__u32)the_kind_of__item), 
            p_PLATFORM_sprite->sprite_texture.gfx, 
            SPRITE_FRAME__8x8__OFFSET);
}

void PLATFORM_update_sprite(
        PLATFORM_Sprite *p_PLATFORM_sprite) {
    uint8_t palette = 0;
    switch (p_PLATFORM_sprite->sprite_texture.sprite_size) {
        default:
        case SpriteSize_8x8:
            break;
        case SpriteSize_16x16:
            palette = 1;
            break;
    }
    oamSet(
            p_PLATFORM_sprite->sprite_texture.oam, 
            p_PLATFORM_sprite->sprite_texture.oam_index, 
            127 - 8, 96 - 8, 
            1, 
            palette,
            p_PLATFORM_sprite->sprite_texture
                .sprite_size, 
            SpriteColorFormat_256Color, 
            p_PLATFORM_sprite->sprite_texture.gfx, 
            -1, 
            false, 
            false, 
            false, false, 
            false);
}

void PLATFORM_set_sprite__position(
        PLATFORM_Sprite *p_PLATFORM_sprite,
        Index__u16 x, Index__u16 y) {
    oamSetXY(
            p_PLATFORM_sprite->sprite_texture.oam,
            p_PLATFORM_sprite->sprite_texture.oam_index,
            x, y);
}
