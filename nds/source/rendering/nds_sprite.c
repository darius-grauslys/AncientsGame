#include "defines.h"
#include "nds/arm9/sprite.h"
#include <rendering/sprite.h>
#include <rendering/texture.h>
#include <entity/entity.h>
#include <nds.h>
#include <debug/debug.h>

#include <assets/entities/player.h>
#include <assets/entities/skeleton.h>
#include <assets/entities/zombie.h>

void PLATFORM_init_oam_sprite__16x16(PLATFORM_Sprite *sprite) {
    PLATFORM_init_texture(
            &sprite->sprite_texture,
            USE_TEXTURE_FLAGS__OAM__16x16(TEXTURE_FLAGS__USE_OAM_MAIN));
}

void PLATFORM_init_oam_sprite__8x8(PLATFORM_Sprite *sprite) {
    PLATFORM_init_texture(
            &sprite->sprite_texture,
            USE_TEXTURE_FLAGS__OAM__8x8(TEXTURE_FLAGS__USE_OAM_MAIN));
}

void PLATFORM_init_sprite(
        PLATFORM_Sprite *sprite,
        Texture_Flags texture_flags_for__sprite,
        bool perform_update) {
    // TODO: debug_warning("PLATFORM_init_sprite is not finished yet:
    //         doesn't support oamSub.");
    uint8_t palette = 0;
    while (DMA_CR(sprite->sprite_texture.dma_channel) & DMA_BUSY);
    switch (texture_flags_for__sprite) {
        default:
            debug_abort("Texture_Flags %d not implemented for PLATFORM_init_sprite.",
                    texture_flags_for__sprite);
            return;
        case TEXTURE_FLAG__SIZE_8x8:
            palette = 0;
            PLATFORM_init_oam_sprite__8x8(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)playerTiles;
            dmaCopy((u8*)playerTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__8x8__OFFSET);
            if (!perform_update)
                break;
            oamSet(
                sprite->sprite_texture.oam, 
                sprite->sprite_texture.oam_index, 
                127 - 8, 96 - 8, 
                1, 
                palette, 
                SpriteSize_8x8, 
                SpriteColorFormat_256Color, 
                0, // null gfx
                -1, 
                false, 
                false, 
                false, false, 
                false);
        case TEXTURE_FLAG__SIZE_16x16:
            palette = 0;
            PLATFORM_init_oam_sprite__16x16(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)playerTiles;
            dmaCopy((u8*)playerTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            if (!perform_update)
                break;
            oamSet(
                sprite->sprite_texture.oam, 
                sprite->sprite_texture.oam_index, 
                127 - 8, 96 - 8, 
                1, 
                palette, 
                SpriteSize_16x16, 
                SpriteColorFormat_256Color, 
                0, // null gfx
                -1, 
                false, 
                false, 
                false, false, 
                false);
            break;
    }
}

void PLATFORM_init_sprite_for__entity(Entity *entity) {
    PLATFORM_Sprite *sprite =
        &entity->sprite_wrapper.sprite;
    uint8_t palette = 0;
    switch(entity->the_kind_of_entity__this_entity_is) {
        default:
            debug_abort("Entity_Kind %d not implemented for PLATFORM_init_entity.",
                    entity->the_kind_of_entity__this_entity_is);
            return;
        case Entity_Kind__Player:
            PLATFORM_init_sprite(&entity->sprite_wrapper.sprite,
                    TEXTURE_FLAG__SIZE_16x16,
                    false);
            sprite->gfx_sprite_sheet = (const uint16_t*)playerTiles;
            dmaCopy((u8*)playerTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            goto oam_16x16;
        case Entity_Kind__Skeleton:
            PLATFORM_init_sprite(&entity->sprite_wrapper.sprite,
                    TEXTURE_FLAG__SIZE_16x16,
                    false);
            sprite->gfx_sprite_sheet = (const uint16_t*)skeletonTiles;
            dmaCopy((u8*)skeletonTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            goto oam_16x16;
        case Entity_Kind__Zombie:
            PLATFORM_init_sprite(&entity->sprite_wrapper.sprite,
                    TEXTURE_FLAG__SIZE_16x16,
                    false);
            sprite->gfx_sprite_sheet = (const uint16_t*)zombieTiles;
            dmaCopy((u8*)zombieTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            goto oam_16x16;
    }

oam_16x16:
    oamSet(
        sprite->sprite_texture.oam, 
        sprite->sprite_texture.oam_index, 
        127 - 8, 96 - 8, 
        1, 
        palette, 
        SpriteSize_16x16, 
        SpriteColorFormat_256Color, 
        sprite->sprite_texture.gfx, 
        -1, 
        false, 
        false, 
        false, false, 
        false);
    return;
}

void PLATFORM_release_sprite(PLATFORM_Sprite *sprite) {
    oamSetHidden(
            sprite->sprite_texture.oam,
            sprite->sprite_texture.oam_index,
            true);
    PLATFORM_free_texture(&sprite->sprite_texture);
}
