#include <entity/controllers/collidable_entity_handlers.h>
#include <collisions/collision_manager.h>
#include <world/chunk_manager.h>

void m_entity_chunk_transition_handler(
        Entity *this_entity,
        Game *game,
        int32_t old_x__chunk,
        int32_t old_y__chunk) {
    debug_warning("m_entity_chunk_transition_handler disabled.");
    return;
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
        Entity *entity_collided) {
    debug_info("collision x,y: %d, %d - %d, %d",
            entity_collision_source->hitbox.x__global,
            entity_collision_source->hitbox.y__global,
            entity_collided->hitbox.x__global,
            entity_collided->hitbox.y__global
            );
    // debug_warning("m_entity_collision_handler not finished.");
}
