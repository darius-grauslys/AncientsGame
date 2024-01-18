#include <entity/controllers/collidable_entity_handlers.h>
#include <collisions/collision_manager.h>
#include <world/chunk_manager.h>

void m_entity_chunk_transition_handler(
        Entity *this_entity,
        Game *game,
        int32_t old_x__chunk,
        int32_t old_y__chunk) {
    remove_entity_from__collision_manager(
            &game->world.collision_manager, 
            this_entity, 
            old_x__chunk, 
            old_y__chunk);
    add_entity_to__collision_manager(
            &game->world.collision_manager, 
            this_entity);
}

void m_local_player_chunk_transition_handler(
        Entity *this_local_player,
        Game *game,
        int32_t old_x__chunk,
        int32_t old_y__chunk) {
    m_entity_chunk_transition_handler(
            this_local_player, 
            game, 
            old_x__chunk, 
            old_y__chunk);
    poll_chunk_manager__for_chunk_movement(
        &game->world.chunk_manager,
        &game->world.world_params,
        this_local_player->hitbox.x__chunk,
        this_local_player->hitbox.y__chunk,
        this_local_player->hitbox.z__chunk);
}

void m_entity_collision_handler(
        Entity *entity_collision_source,
        Entity *entity_collided) {
    debug_warning("m_entity_collision_handler not finished.");
}
