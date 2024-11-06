#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "defines_weak.h"
#include <defines.h>

void initialize_structure(
        Structure *p_structure);

void add_p_room_to__structure(
        Structure *p_structure,
        Room *p_room);

///
/// Returns quantity of rooms in the structure
/// and assigns a ptr_array to point to
/// the rooms.
///
/// If the structure has less rooms than
/// ROOMS_IN_STRUCTURE__MAX_QUANTITY_OF then
/// the index following the last room will be null.
/// The indices following that index will be undefined!
///
void get_rooms_in__structure(
        Structure *p_structure,
        Structure_Ptr_Array_Of__Rooms ptr_array_of__rooms);

static inline
Quantity__u32 get_quantity_of__rooms_in__structure(
        Structure *p_structure) {
    return p_structure->quantity_of__rooms_in__structure;
}

static inline
Structure_Type__u16 get_the_kind_of__structure(
        Structure *p_structure) {
    return p_structure->the_kind_of__structure;
}

static inline
void set_the_kind_of__structure(
        Structure *p_structure,
        Structure_Type__u16 the_kind_of__structure) {
    p_structure->the_kind_of__structure =
        the_kind_of__structure;
}

static inline
bool is_structure__allocated(
        Structure *p_structure) {
    return p_structure->structure_flags
        & STRUCTURE_FLAG__IS_ALLOCATED
        ;
}

static inline
void set_structure_as__allocated(
        Structure *p_structure) {
    p_structure->structure_flags |=
        STRUCTURE_FLAG__IS_ALLOCATED
        ;
}

static inline
void set_structure_as__deallocated(
        Structure *p_structure) {
    p_structure->structure_flags &=
        ~STRUCTURE_FLAG__IS_ALLOCATED
        ;
}

#endif
