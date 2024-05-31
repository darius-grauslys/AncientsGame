#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <defines.h>

void init_entity_manager(Entity_Manager *p_entity_manager);

///
/// Return nullptr (0) if fails to get new entity.
///
Entity *allocate__entity(
        Entity_Manager *p_entity_manager,
        enum Entity_Kind kind_of_entity);
void release_entity_from__entity_manager(
        Entity_Manager *p_manager, 
        Entity *p_entity);

static Entity inline *get_entity_ptr_from__entity_manager(
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

Entity *get_new__entity( 
        Entity_Manager *p_entity_manager, 
        enum Entity_Kind kind_of_entity,
        Vector__3i32F4 position__3i32F4);

#endif
