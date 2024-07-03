#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "defines_weak.h"
#include <defines.h>
#include <debug/debug.h>

void initialize_entity_manager(Entity_Manager *p_entity_manager);

///
/// Create a new entity instance within the entity_manager object pool.
/// Return nullptr (0) if fails to get new entity.
///
Entity *allocate_entity_in__entity_manager(
        Entity_Manager *p_entity_manager,
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position,
        PLATFORM_Graphics_Window
            *p_PLATFORM_graphics_window);

///
/// Release entity from the entity_manager object pool.
///
void release_entity_from__entity_manager(
        Entity_Manager *p_manager, 
        Entity *p_entity);

///
/// Translate entity ID to entity ptr.
///
static Entity inline *get_p_entity_from__entity_manager(
        Entity_Manager *p_entity_manager,
        Identifier__u16 id) {
#ifndef NDEBUG
    if (ENTITY_MAXIMUM_QUANTITY_OF <= id) {
        debug_abort("Index out of bounds %d, \
get_entity_ptr_from__entity_manager",
                id);
        return 0;
    }
#endif
    return &p_entity_manager->entities[id];
}

#endif
