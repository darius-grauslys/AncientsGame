#ifndef ROOM_H
#define ROOM_H

#include "defines_weak.h"
#include "vectors.h"
#include <defines.h>

void initialize_room(
        Room *p_room);

void add_entrance_to__room(
        Room *p_room,
        Vector__3i32F4 position__3i32F4);

///
/// Returns VECTOR__3i32F4__OUT_OF_BOUNDS on failure.
///
Vector__3i32F4 get_closest_entrance_to__room(
        Room *p_room,
        Vector__3i32F4 position__3i32F4);

static inline
Quantity__u32 get_quantity_of__entrances_in__room(
        Room *p_room) {
    return p_room->quantity_of__room_entrances;
}

static inline
Quantity__u32 get_width_of__room(
        Room *p_room) {
    return p_room->bounding_box_of__room.width__quantity_u32;
}

static inline
Quantity__u32 get_height_of__room(
        Room *p_room) {
    return p_room->bounding_box_of__room.height__quantity_u32;
}

static inline
Room_Type__u16 get_the_type_of__room(
        Room *p_room) {
    return p_room->the_type_of__room;
}

static inline
Room_Type__u16 set_the_type_of__room(
        Room *p_room,
        Room_Type__u16 the_type_of__room) {
    p_room->the_type_of__room =
        the_type_of__room;
}

static inline
bool is_room__allocated(
        Room *p_room) {
    return p_room->room_flags
        & ROOM_FLAG__IS_ALLOCATED
        ;
}

static inline
void set_room_as__allocated(
        Room *p_room) {
    p_room->room_flags |=
        ROOM_FLAG__IS_ALLOCATED;
}

static inline
void set_room_as__deallocated(
        Room *p_room) {
    p_room->room_flags &=
        ~ROOM_FLAG__IS_ALLOCATED;
}

#endif
