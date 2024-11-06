#ifndef STRUCTURE_MANAGER_H
#define STRUCTURE_MANAGER_H

#include <defines.h>

void initialize_structure_manager(
        Structure_Manager *p_structure_manager);

Room *allocate_room_in__structure_manager(
        Structure_Manager *p_structure_manager);

Structure *allocate_structure_in__structure_manager(
        Structure_Manager *p_structure_manager);

void release_room_in__structure_manager(
        Structure_Manager *p_structure_manager,
        Room *p_room);

void release_structure_in__structure_manager(
        Structure_Manager *p_structure_manager,
        Structure *p_structure);

static inline
Quantity__u32 get_quantity_of__rooms_allocated_in__structure_manager(
        Structure_Manager *p_structure_manager) {
    return p_structure_manager->quantity_of__allocated_rooms;
}

static inline
Quantity__u32 get_quantity_of__structures_allocated_in__structure_manager(
        Structure_Manager *p_structure_manager) {
    return p_structure_manager->quantity_of__allocated_structures;
}

#endif
