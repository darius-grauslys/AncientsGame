#include <entity/controllers/collidable_entity_handlers.h>
#include <collisions/collision_manager.h>
#include <world/chunk_manager.h>

void m_entity_chunk_transition_handler(
        Entity *this_entity,
        Game *game,
        int32_t old_x__chunk,
        int32_t old_y__chunk) {
    // debug_warning("m_entity_chunk_transition_handler disabled.");
    // return;
    remove_entity_from__collision_manager(
            &game->world.collision_manager, 
            this_entity, 
            old_x__chunk, 
            old_y__chunk);
    add_entity_to__collision_manager(
            &game->world.collision_manager, 
            this_entity);
}

void m_entity_collision_handler(
        Entity *entity_collision_source,
        Entity *entity_collided,
        Direction direction_of_collision) {
    if (direction_of_collision & DIRECTION__NORTH
            || direction_of_collision & DIRECTION__SOUTH) {
        entity_collision_source->hitbox.y__velocity *= -1;
    }
    if (direction_of_collision & DIRECTION__EAST
            || direction_of_collision & DIRECTION__WEST) {
        entity_collision_source->hitbox.x__velocity *= -1;
    }
}
