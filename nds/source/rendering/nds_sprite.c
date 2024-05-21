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

void PLATFORM_init_sprite(
        PLATFORM_Sprite *sprite,
        enum Entity_Kind entity_kind) {
    // debug_warning("PLATFORM_init_sprite is not finished yet: \
    //         doesn't support oamSub.");
    uint8_t palette = 0;
    while (DMA_CR(sprite->sprite_texture.dma_channel) & DMA_BUSY);
    switch (entity_kind) {
        case Entity_Kind__Item:
        case Entity_Kind__Particle:
            debug_abort("Entity type not implemented for PLATFORM_init_sprite.");
            return;
        case Entity_Kind__Player:
            palette = 0;
            PLATFORM_init_oam_sprite__16x16(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)playerTiles;
            dmaCopy((u8*)playerTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            break;
        case Entity_Kind__Skeleton:
            palette = 0;
            PLATFORM_init_oam_sprite__16x16(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)skeletonTiles;
            dmaCopy((u8*)skeletonTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            break;
        case Entity_Kind__Zombie:
            palette = 0;
            PLATFORM_init_oam_sprite__16x16(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)zombieTiles;
            dmaCopy((u8*)zombieTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME__16x16__OFFSET);
            break;
    }

    oamSet(
        sprite->sprite_texture.oam, 
        sprite->sprite_texture.oam_index, 
        127 - 8, 96 - 8, 
        0, 
        palette, 
        SpriteSize_16x16, 
        SpriteColorFormat_256Color, 
        sprite->sprite_texture.gfx, 
        -1, 
        false, 
        false, 
        false, false, 
        false);
}

void PLATFORM_release_sprite(PLATFORM_Sprite *sprite) {
    oamSetHidden(
            sprite->sprite_texture.oam,
            sprite->sprite_texture.oam_index,
            true);
    PLATFORM_free_texture(&sprite->sprite_texture);
}
