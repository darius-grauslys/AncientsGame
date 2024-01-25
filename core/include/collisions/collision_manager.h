#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <defines.h>

void init_collision_manager(
        Collision_Manager *collision_manager);

void poll_collision_manager(
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
/// TODO: note, if the change in center_chunk
/// is sufficently large, this is very
/// performance heavy. This should be better
/// renamed to move_, and later on have
/// a set_ for each chunk_manager and collision_manager
/// which will fully reset internal data and before a
/// large jump. Good if the player teleports for whatever
/// reason.
///
void set_collision_manager__center_chunk(
        Collision_Manager *collision_manager,
        int32_t x__center_chunk,
        int32_t y__center_chunk);

#endif
