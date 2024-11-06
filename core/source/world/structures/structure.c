#include "defines.h"
#include "defines_weak.h"
#include "world/structures/room.h"
#include <world/structures/structure.h>

static inline
Room *get_p_room_by__index_in__structure(
        Structure *p_structure,
        Index__u8 index_of__room) {
    return p_structure->ptr_array_of__rooms[index_of__room];
}

static inline
void set_p_room_by__index_in__structure(
        Structure *p_structure,
        Index__u8 index_of__room,
        Room *p_room) {
    p_structure->ptr_array_of__rooms[index_of__room] =
        p_room;
}

void initialize_structure(
        Structure *p_structure) {
    p_structure->the_kind_of__structure = 0;
    p_structure->quantity_of__rooms_in__structure = 0;
    p_structure->structure_flags =
        STRUCTURE_FLAGS__NONE;

    for (Index__u32 index_of__room = 0;
            index_of__room
            < ROOMS_IN_STRUCTURE__MAX_QUANTITY_OF;
            index_of__room++) {
        set_p_room_by__index_in__structure(
                p_structure, 
                index_of__room, 
                0);
    }
}

void add_p_room_to__structure(
        Structure *p_structure,
        Room *p_room) {
    set_p_room_by__index_in__structure(
            p_structure, 
            p_structure->quantity_of__rooms_in__structure++,
            p_room);
}

void get_rooms_in__structure(
        Structure *p_structure,
        Structure_Ptr_Array_Of__Rooms ptr_array_of__rooms) {
    Quantity__u32 quantity_of__rooms =
        get_quantity_of__rooms_in__structure(p_structure);
    for (Index__u32 index_of__room = 0;
            index_of__room
            < ROOMS_IN_STRUCTURE__MAX_QUANTITY_OF;
            index_of__room++) {
        if (index_of__room >= quantity_of__rooms) {
            ptr_array_of__rooms[index_of__room] = 0;
            return;
        }
        ptr_array_of__rooms[index_of__room] =
            get_p_room_by__index_in__structure(
                    p_structure, 
                    index_of__room);
    }
}
