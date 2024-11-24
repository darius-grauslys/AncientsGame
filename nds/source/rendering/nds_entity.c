#include "game.h"
#include <rendering/render_entity.h>
#include <entity/entity.h>
#include <nds.h>
#include <collisions/hitbox_aabb.h>
#include <vectors.h>
#include <nds_defines.h>
#include "rendering/nds_sprite.h"

void PLATFORM_render_entity(
        Entity *p_entity,
        Game *p_game) {
    if (is_entity_not__updating_graphics(p_entity)) {
        return;
    }

    PLATFORM_Sprite *p_PLATFORM_sprite =
        p_entity->sprite_wrapper.p_sprite;
    Camera *p_camera =
        get_p_camera_from__game(p_game);

    if (is_entity_not__updating_position(p_entity)) {
        NDS_set_position_of__PLATFORM_sprite(
                p_PLATFORM_sprite, 
                127 - 8, 96 - 8);
    } else {
        int32_t x__origin, y__origin;
        int32_t x__global, y__global;
        x__origin = get_x_i32_from__vector_3i32F4(p_camera->position);
        y__origin = get_y_i32_from__vector_3i32F4(p_camera->position);

        x__global = get_x_i32_from__entity(p_entity);
        y__global = get_y_i32_from__entity(p_entity);

        if (abs(x__global - x__origin) > 256 / 2 + 16
                || abs(y__global - y__origin) > 196 / 2 + 16) {
            set_entity_as__hidden(p_entity);
            NDS_set_hidden__PLATFORM_sprite(
                    p_PLATFORM_sprite, 
                    true);
            return;
        } else {
            set_entity_as__visible(p_entity);
            NDS_set_hidden__PLATFORM_sprite(
                    p_PLATFORM_sprite, 
                    false);
        }

        NDS_set_position_of__PLATFORM_sprite(
                p_PLATFORM_sprite, 
            x__global - x__origin + 127 - 8,
            -(y__global - y__origin - 96 + 8));
    }

    if (p_entity->sprite_wrapper.direction & DIRECTION__WEST) {
        NDS_set_flip_of__PLATFORM_sprite(
                p_PLATFORM_sprite, 
                true,
                false);
    } else {
        NDS_set_flip_of__PLATFORM_sprite(
                p_PLATFORM_sprite, 
                false,
                false);
    }
}
