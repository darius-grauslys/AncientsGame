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
        int32_t x__global, y__global;
        x__global = get_global_x_from__hitbox(&entity->hitbox);
        y__global = get_global_y_from__hitbox(&entity->hitbox);
        int32_t x__global_player, y__global_player;
        x__global_player = get_global_x_from__hitbox(&local_player->hitbox);
        y__global_player = get_global_y_from__hitbox(&local_player->hitbox);

        if (abs(x__global - x__global_player) > 256 / 2 + 16
                || abs(y__global - y__global_player) > 196 / 2 + 16) {
            set_entity_as__hidden(entity);
            oamSetHidden(
                    sprite->sprite_texture.oam,
                    sprite->sprite_texture.oam_index,
                    true);
            return;
        } else {
            set_entity_as__visible(entity);
            oamSetHidden(
                    sprite->sprite_texture.oam,
                    sprite->sprite_texture.oam_index,
                    false);
        }

        oamSetXY(
            sprite->sprite_texture.oam, 
            sprite->sprite_texture.oam_index, 
            x__global - x__global_player + 127 - 8,
            -(y__global - y__global_player - 96 + 8));
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
