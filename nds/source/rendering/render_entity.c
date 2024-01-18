#include <rendering/render_entity.h>
#include <entity/entity.h>
#include <nds.h>

void PLATFORM_render_entity(
        Entity *entity,
        Game *game) {
    if (is_entity_not__updating_graphics(entity)) {
        return;
    }

    PLATFORM_Sprite *sprite =
        &entity->sprite_wrapper.sprite;

    Entity *local_player = game->world.entity_manager.local_player;

    if (is_entity_not__updating_position(entity)) {
        oamSetXY(
            sprite->sprite_texture.oam, 
            sprite->sprite_texture.oam_index, 
            127 - 8, 96 - 8);
    } else {
        oamSetXY(
            sprite->sprite_texture.oam, 
            sprite->sprite_texture.oam_index, 
            ((entity->x__chunk - local_player->x__chunk) << 
                ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
                + ((entity->x - local_player->x) >> 
                    ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE), 
            -(((entity->y__chunk - local_player->y__chunk) << 
                ENTITY_CHUNK_LOCAL_SPACE__BIT_SIZE) 
                + ((entity->y - local_player->y) >> 
                    ENTITY_VELOCITY_FRACTIONAL__BIT_SIZE))
            );
    }

    if (entity->sprite_wrapper.direction & DIRECTION__WEST) {
        oamSetFlip(
                sprite->sprite_texture.oam,
                sprite->sprite_texture.oam_index,
                true,
                false);

    } else {
        oamSetFlip(
                sprite->sprite_texture.oam,
                sprite->sprite_texture.oam_index,
                false,
                false);
    }
}
