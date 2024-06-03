#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <defines.h>

void initialize_collision_manager(
        Collision_Manager *collision_manager);

///
/// Check if this entity is colliding
/// into anything. If so, it will
/// invoke the entity's collision
/// handler if it has one.
///
/// Returns true if entity is still
/// in bounds, otherwise return false.
///
bool poll_collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity);

///
/// Does nothing if cannot find
/// entity.
///
/// If NDEBUG is not set, then it
/// will debug_error(...)
///
void remove_entity_from__collision_manager__at(
        Collision_Manager *collision_manager,
        Entity *entity,
        Signed_Index__i32 old_x__chunk__signed_index_i32,
        Signed_Index__i32 old_y__chunk__signed_index_i32);

///
/// Does nothing if cannot find
/// entity.
///
/// If NDEBUG is not set, then it
/// will debug_error(...)
///
static void inline remove_entity_from__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity) {
    remove_entity_from__collision_manager__at(
            collision_manager,
            entity,
            entity->hitbox.chunk_index__3i32.x__i32,
            entity->hitbox.chunk_index__3i32.y__i32);
}

///
/// Returns true if successful
/// otherwise returns false if
/// out of bounds, or collision node
/// is full.
///
/// If the collision node is full,
/// are you tring to add a particle
/// to the collision_manager? Don't do that!
///
bool add_entity_to__collision_manager(
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
        Signed_Index__i32 x__center_chunk__signed_index_i32,
        Signed_Index__i32 y__center_chunk__signed_index_i32);

static bool inline is_in_bounds_of__collision_manager(
        Collision_Manager *collision_manager,
        Signed_Index__i32 x__chunk__signed_index_i32,
        Signed_Index__i32 y__chunk__signed_index_i32) {
    return (x__chunk__signed_index_i32 
            < collision_manager->x__center_chunk__signed_index_i32
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2)
        &&
        (x__chunk__signed_index_i32 
         >= collision_manager->x__center_chunk__signed_index_i32 
         - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2)
        &&
        (y__chunk__signed_index_i32 
         < collision_manager->y__center_chunk__signed_index_i32
         + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS / 2)
        &&
        (y__chunk__signed_index_i32 
         >= collision_manager->y__center_chunk__signed_index_i32
         - CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS / 2);
}

#endif
