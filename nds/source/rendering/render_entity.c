#include <rendering/render_entity.h>
#include <entity/entity.h>
#include <nds.h>
#include <collisions/hitbox_aabb.h>

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
            get_global_x_from__hitbox(&entity->hitbox)
                - get_global_x_from__hitbox(&local_player->hitbox) + 127 - 8,
            -(get_global_y_from__hitbox(&entity->hitbox)
                - get_global_y_from__hitbox(&local_player->hitbox) - 96 + 8)
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
