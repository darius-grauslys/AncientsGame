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
        Entity *entity) {
    while (DMA_CR(sprite->sprite_texture.dma_channel) & DMA_BUSY);
    switch (entity->the_kind_of_entity__this_entity_is) {
        case Entity_Kind__Item:
        case Entity_Kind__Particle:
            debug_abort("Entity type not implemented for PLATFORM_init_sprite.");
            return;
        case Entity_Kind__Player:
            PLATFORM_init_oam_sprite__16x16(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)playerTiles;
            dmaCopy((u8*)playerTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME_WIDTH__ENTITY_HUMANOID
                    * SPRITE_FRAME_HEIGHT__ENTITY_HUMANOID);
            return;
        case Entity_Kind__Skeleton:
            PLATFORM_init_oam_sprite__16x16(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)skeletonTiles;
            dmaCopy((u8*)skeletonTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME_WIDTH__ENTITY_HUMANOID
                    * SPRITE_FRAME_HEIGHT__ENTITY_HUMANOID);
            return;
        case Entity_Kind__Zombie:
            PLATFORM_init_oam_sprite__16x16(sprite);
            sprite->gfx_sprite_sheet = (const uint16_t*)zombieTiles;
            dmaCopy((u8*)zombieTiles, sprite->sprite_texture.gfx, 
                    SPRITE_FRAME_WIDTH__ENTITY_HUMANOID
                    * SPRITE_FRAME_HEIGHT__ENTITY_HUMANOID);
            return;
    }
}
