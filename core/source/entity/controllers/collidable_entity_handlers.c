#include <entity/controllers/collidable_entity_handlers.h>
#include <collisions/collision_manager.h>
#include <world/chunk_manager.h>

void m_entity_collision_handler(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction direction_of_collision) {
    if (direction_of_collision & DIRECTION__NORTH) {
        entity_collision_source->hitbox
            .y__velocity = -ENTITY_VELOCITY__PLAYER;
    }
    if (direction_of_collision & DIRECTION__SOUTH) {
        entity_collision_source->hitbox
            .y__velocity = ENTITY_VELOCITY__PLAYER;
    }
    if (direction_of_collision & DIRECTION__EAST) {
        entity_collision_source->hitbox
            .x__velocity = -ENTITY_VELOCITY__PLAYER;
    }
    if (direction_of_collision & DIRECTION__WEST) {
        entity_collision_source->hitbox
            .x__velocity = ENTITY_VELOCITY__PLAYER;
    }
}
