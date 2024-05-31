#include <entity/controllers/body/collidable_entity_handlers.h>
#include <collisions/collision_manager.h>
#include <collisions/hitbox_aabb.h>
#include <world/chunk_manager.h>

void m_entity_collision_handler(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction__u8 direction_of_collision) {
    int32_t source_x =
        get_global_x_from__hitbox(&entity_collision_source->hitbox);
    int32_t source_y =
        get_global_y_from__hitbox(&entity_collision_source->hitbox);

    int32_t collided_x =
        get_global_x_from__hitbox(&entity_collided->hitbox);
    int32_t collided_y =
        get_global_y_from__hitbox(&entity_collided->hitbox);

    int32_t delta_x = 
        source_x - collided_x;
    int32_t delta_y = 
        source_y - collided_y;


    debug_info("collide: %d, %d < %d",
            delta_x * delta_x,
            delta_y * delta_y,
            COLLISION_DELTA_THRESHOLD);
    if (delta_x * delta_x > COLLISION_DELTA_THRESHOLD) {
        set_x_velocity_to__hitbox(
                &entity_collided->hitbox, 
                (source_x < collided_x) ? delta_x/2 + 1 : -delta_x/2 - 1
                );
        set_x_velocity_to__hitbox(
                &entity_collision_source->hitbox, 
                (collided_x < source_x) ? delta_x/2 + 1 : -delta_x/2 - 1
                );
    }

    if (delta_y * delta_y > COLLISION_DELTA_THRESHOLD) {
        set_y_velocity_to__hitbox(
                &entity_collided->hitbox, 
                (source_y < collided_y) ? -delta_y/2 - 1 : delta_y/2 + 1
                );
        set_y_velocity_to__hitbox(
                &entity_collision_source->hitbox, 
                (collided_y < source_y) ? -delta_y/2 - 1 : delta_y/2 + 1
                );
    }
}

void m_entity_tile_collision_handler(
        Entity *entity_collision_source,
        Tile *tile_collided) {
    //TODO: improve lol.

    entity_collision_source->hitbox.velocity__3i32F4.x__i32F4 *= -1;
    entity_collision_source->hitbox.velocity__3i32F4.y__i32F4 *= -1;
    entity_collision_source->hitbox.velocity__3i32F4.z__i32F4 *= -1;
}
