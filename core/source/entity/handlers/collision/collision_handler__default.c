#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "platform_defines.h"
#include "vectors.h"
#include "world/tile_vectors.h"
#include <entity/handlers/collision/collision_handler__default.h>
#include <collisions/collision_manager.h>
#include <collisions/hitbox_aabb.h>
#include <world/chunk_manager.h>

void m_entity_collision_handler__default(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction__u8 direction_of_collision,
        Game *p_game) {
    int32_t source_x = get_x_i32F4_from__entity(entity_collision_source);
    int32_t source_y = get_y_i32F4_from__entity(entity_collision_source);
    int32_t collided_x = get_x_i32F4_from__entity(entity_collided);
    int32_t collided_y = get_y_i32F4_from__entity(entity_collided);

    int32_t delta_x = 
        source_x - collided_x;
    int32_t delta_y = 
        source_y - collided_y;

    Quantity__u32 width_of__source =
        entity_collision_source->hitbox.width__quantity_u32;
    Quantity__u32 width_of__collided =
        entity_collided->hitbox.width__quantity_u32;
    Quantity__u32 height_of__source =
        entity_collision_source->hitbox.height__quantity_u32;
    Quantity__u32 height_of__collided =
        entity_collided->hitbox.height__quantity_u32;

    Signed_Quantity__i32 ideal_delta_x =
        width_of__collided + width_of__source;
    Signed_Quantity__i32 ideal_delta_y =
        height_of__collided + height_of__source;


    if (delta_x * delta_x < COLLISION_DELTA_THRESHOLD) {
        entity_collided->hitbox.velocity__3i32F4.x__i32F4 = 
            (ideal_delta_x - delta_x) >> 2
            ;
        entity_collision_source->hitbox.velocity__3i32F4.x__i32F4 =
            (ideal_delta_x + delta_x) >> 2
            ;
    }

    if (delta_y * delta_y < COLLISION_DELTA_THRESHOLD) {
        entity_collided->hitbox.velocity__3i32F4.y__i32F4 =
            (ideal_delta_y - delta_y) >> 2
            ;
        entity_collision_source->hitbox.velocity__3i32F4.y__i32F4 = 
            (ideal_delta_y + delta_y) >> 2
            ;
    }
}

void m_entity_tile_collision_handler__default(
        Entity *entity_collision_source,
        Tile *tile_collided,
        Signed_Quantity__i32 x_collision__i32,
        Signed_Index__i32 y_collision__i32,
        Direction__u8 direction_of__tile_collision) {
    Vector__3i32F4 tile_center =
        get_vector__3i32F4(
                x_collision__i32, 0b1000, 
                y_collision__i32, 0b1000, 
                0, 0);

    Signed_Index__i32 delta_x =
        get_x_i32F4_from__entity(entity_collision_source)
        - tile_center.x__i32F4;
    Signed_Index__i32 delta_y =
        get_y_i32F4_from__entity(entity_collision_source)
        - tile_center.y__i32F4;

    Signed_Index__i32 ideal_delta_x =
        (TILE_WIDTH__IN_PIXELS
        + entity_collision_source->hitbox.width__quantity_u32)
        >> 2;
    Signed_Index__i32 ideal_delta_y =
        (TILE_WIDTH__IN_PIXELS
        + entity_collision_source->hitbox.height__quantity_u32)
        >> 2;

    if (delta_x * delta_x >= delta_y * delta_y) {
        entity_collision_source->hitbox.velocity__3i32F4.x__i32F4 =
            -(ideal_delta_x - delta_x) >> 2
            ;
    }
    if (delta_x * delta_x <= delta_y * delta_y) {
        entity_collision_source->hitbox.velocity__3i32F4.y__i32F4 =
            -(ideal_delta_y - delta_y) >> 2
            ;
    }

    //TODO: 3d
    entity_collision_source->hitbox.velocity__3i32F4.z__i32F4 *= 0;
}
