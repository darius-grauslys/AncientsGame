#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <defines.h>

void init_collision_manager(
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
        int32_t old_x__chunk,
        int32_t old_y__chunk);

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
            entity->hitbox.x__chunk,
            entity->hitbox.y__chunk);
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
/// Call this every time after calling
/// move_chunk_manager(...)
///
void move_collision_manager(
        Collision_Manager *collision_manager,
        Direction direction,
        uint32_t steps);

///
/// Call this every time after calling
/// set_chunk_manager_at__position(...)
///
/// NOTICE: if you call this function
/// you must re-add any and all entities
/// BACK into the collision_manager!
///
/// TODO: Can we try to do better in
/// the re-add entity regard?
///
void set_collision_manager_at__position(
        Collision_Manager *collision_manager,
        int32_t x__center_chunk,
        int32_t y__center_chunk);

static bool inline is_in_bounds_of__collision_manager(
        Collision_Manager *collision_manager,
        int32_t x__chunk,
        int32_t y__chunk) {
    return (x__chunk < collision_manager->x__center_chunk 
            + CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2)
        &&
        (x__chunk >= collision_manager->x__center_chunk 
         - CHUNK_MANAGER__QUANTITY_OF_CHUNKS__PER_ROW / 2)
        &&
        (y__chunk < collision_manager->y__center_chunk 
         + CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS / 2)
        &&
        (y__chunk >= collision_manager->y__center_chunk 
         - CHUNK_MANAGER__QUANTITY_OF_MANAGED_CHUNK_ROWS / 2);
}

#endif
