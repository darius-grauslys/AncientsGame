#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "vectors.h"
#include <world/structures/room.h>

static inline
Vector__3i32F4 get_room_entrance_by__index(
        Room *p_room,
        Index__u32 index_of__entrance) {
#ifndef NDEBUG
    if (index_of__entrance
            >= ROOM_ENTRANCE_MAX_QUANTITY_OF) {
        debug_error("get_room_entrance_by__index, out of bounds: %d",
                index_of__entrance);
        return VECTOR__3i32F4__OUT_OF_BOUNDS;
    }
#endif
    return p_room->entrances__3i32F4[index_of__entrance];
}

static inline
void set_room_entrance_by__index(
        Room *p_room,
        Index__u32 index_of__entrance,
        Vector__3i32F4 position_of__entrance__3i32F4) {
#ifndef NDEBUG
    if (index_of__entrance
            >= ROOM_ENTRANCE_MAX_QUANTITY_OF) {
        debug_error("set_room_entrance_by__index, out of bounds: %d",
                index_of__entrance);
        return;
    }
#endif
    p_room->entrances__3i32F4[index_of__entrance] =
        position_of__entrance__3i32F4;
}

void initialize_room(
        Room *p_room) {
    initialize_hitbox(
            &p_room->bounding_box_of__room, 
            1, 
            1, 
            VECTOR__3i32F4__OUT_OF_BOUNDS);

    p_room->room_flags =
        ROOM_FLAGS__NONE;
    p_room->quantity_of__room_entrances = 0;
    p_room->the_type_of__room = 0;
    
    for (Index__u32 index_of__entrance = 0;
            index_of__entrance
            < ROOMS_IN_STRUCTURE__MAX_QUANTITY_OF;
            index_of__entrance++) {
        set_room_entrance_by__index(
                p_room, 
                index_of__entrance, 
                VECTOR__3i32F4__OUT_OF_BOUNDS);
    }
}

void add_entrance_to__room(
        Room *p_room,
        Vector__3i32F4 position__3i32F4) {
    if (get_quantity_of__entrances_in__room(p_room)
            >= ROOM_ENTRANCE_MAX_QUANTITY_OF) {
        debug_error("add_entrance_to__room, max quantity of rooms reached.");
        return;
    }

    set_room_entrance_by__index(
            p_room, 
            get_quantity_of__entrances_in__room(p_room), 
            position__3i32F4);
    p_room->quantity_of__room_entrances++;
}

Vector__3i32F4 get_closest_entrance_to__room(
        Room *p_room,
        Vector__3i32F4 position__3i32F4) {
    i32F4 shortest_distance = I32F4_MAX;
    Vector__3i32F4 entrance_that_is__closest =
        VECTOR__3i32F4__OUT_OF_BOUNDS;
    for (Index__u32 index_of__entrance = 0;
            index_of__entrance
            < ROOM_ENTRANCE_MAX_QUANTITY_OF
            && index_of__entrance
            < get_quantity_of__entrances_in__room(p_room);
            index_of__entrance++) {
        Vector__3i32F4 entrance =
            get_room_entrance_by__index(
                    p_room, 
                    index_of__entrance);
        if (is_vectors_3i32F4__out_of_bounds(
                    entrance)) {
            continue;
        }

        i32F4 distance = 
            get_distance_squared_of__vector_3i32F4(
                    subtract_vectors__3i32F4(
                        position__3i32F4, 
                        entrance));

        if (distance >= shortest_distance)
            continue;

        entrance_that_is__closest =
            entrance;
    }

    return entrance_that_is__closest;
}
