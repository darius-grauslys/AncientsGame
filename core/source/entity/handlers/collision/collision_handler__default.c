#include "entity/entity.h"
#include <entity/handlers/collision/collision_handler__default.h>
#include <collisions/collision_manager.h>
#include <collisions/hitbox_aabb.h>
#include <world/chunk_manager.h>

void m_entity_collision_handler__default(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction__u8 direction_of_collision) {
    int32_t source_x = get_x_i32_from__entity(entity_collision_source);
    int32_t source_y = get_y_i32_from__entity(entity_collision_source);
    int32_t collided_x = get_x_i32_from__entity(entity_collided);
    int32_t collided_y = get_y_i32_from__entity(entity_collided);

    int32_t delta_x = 
        source_x - collided_x;
    int32_t delta_y = 
        source_y - collided_y;


    debug_info("collide: %d, %d < %d",
            delta_x * delta_x,
            delta_y * delta_y,
            COLLISION_DELTA_THRESHOLD);
    if (delta_x * delta_x > COLLISION_DELTA_THRESHOLD) {
        entity_collided->hitbox.velocity__3i32F4.x__i32F4 = 
                (source_x < collided_x) ? delta_x/2 + 1 : -delta_x/2 - 1
                ;
        entity_collision_source->hitbox.velocity__3i32F4.x__i32F4 =
                (collided_x < source_x) ? delta_x/2 + 1 : -delta_x/2 - 1
                ;
    }

    if (delta_y * delta_y > COLLISION_DELTA_THRESHOLD) {
        entity_collided->hitbox.velocity__3i32F4.y__i32F4 =
                (source_y < collided_y) ? -delta_y/2 - 1 : delta_y/2 + 1
                ;
        entity_collision_source->hitbox.velocity__3i32F4.y__i32F4 = 
                (collided_y < source_y) ? -delta_y/2 - 1 : delta_y/2 + 1
                ;
    }
}

void m_entity_tile_collision_handler__default(
        Entity *entity_collision_source,
        Tile *tile_collided) {
    //TODO: improve lol.

    entity_collision_source->hitbox.velocity__3i32F4.x__i32F4 *= -1;
    entity_collision_source->hitbox.velocity__3i32F4.y__i32F4 *= -1;
    entity_collision_source->hitbox.velocity__3i32F4.z__i32F4 *= -1;
}
