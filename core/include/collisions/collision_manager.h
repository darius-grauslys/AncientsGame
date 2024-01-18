#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <defines.h>

void init_collision_manager(
        Collision_Manager *collision_manager);

void poll_collision_mannager(
        Collision_Manager *collision_manager,
        Entity *entity);

void remove_entity_from__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity,
        int32_t old_x__chunk,
        int32_t old_y__chunk);

void add_entity_to__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity);

///
/// Call this after each time you call
/// move_chunk_manager__chunks(...)
///
void update_collision_manager(
        Collision_Manager *collision_manager,
        World *world,
        Game *game);

#endif
