#include "defines.h"
#include "defines_weak.h"
#include "platform_defines.h"
#include "world/structures/structure.h"
#include "world/structures/room.h"
#include <world/structures/structure_manager.h>

static inline
Room *get_p_room_by__index_in__structure_manager(
        Structure_Manager *p_structure_manager,
        Index__u32 index_of__room) {
#ifndef NDEBUG
    if (index_of__room >=
            STRUCTURE_MAX_QUANTITY_OF) {
        debug_error("get_p_room_by__index_in__structure_manager, index out of bounds: %d", index_of__room);
        return 0;
    }
#endif
    return &p_structure_manager
        ->rooms[index_of__room];
}

static inline
Structure *get_p_structure_by__index_in__structure_manager(
        Structure_Manager *p_structure_manager,
        Index__u32 index_of__structure) {
#ifndef NDEBUG
    if (index_of__structure >=
            STRUCTURE_MAX_QUANTITY_OF) {
        debug_error("get_p_structure_by__index_in__structure_manager, index out of bounds: %d", index_of__structure);
        return 0;
    }
#endif
    return &p_structure_manager
        ->structures[index_of__structure];
}

Room *find_available_room_in__structure_manager(
        Structure_Manager *p_structure_manager) {
    Index__u32 index_of__room__beginning =
        get_quantity_of__rooms_allocated_in__structure_manager(
                p_structure_manager)
        % ROOMS_IN_STRUCTURE__MAX_QUANTITY_OF;
    Index__u32 index_of__room__current =
        index_of__room__beginning;
    Room *p_room__selected = 0;
    do {
        Room *p_room = 
            get_p_room_by__index_in__structure_manager(
                    p_structure_manager, 
                    index_of__room__current);

        if (!is_room__allocated(p_room))
            continue;
        p_room__selected = p_room;
        break;
    } while (
            (index_of__room__current =
                (index_of__room__current+1)
                % ROOM_ENTRANCE_MAX_QUANTITY_OF)
            != index_of__room__beginning);

    if (!p_room__selected)
        return 0;

    return p_room__selected;
}

Structure *find_available_structure_in__structure_manager(
        Structure_Manager *p_structure_manager) {
    Index__u32 index_of__structure__beginning =
        get_quantity_of__structures_allocated_in__structure_manager(
                p_structure_manager)
        % ROOMS_IN_STRUCTURE__MAX_QUANTITY_OF;
    Index__u32 index_of__structure__current =
        index_of__structure__beginning;
    Structure *p_structure__selected = 0;
    do {
        Structure *p_structure = 
            get_p_structure_by__index_in__structure_manager(
                    p_structure_manager, 
                    index_of__structure__current);

        if (!is_structure__allocated(p_structure))
            continue;
        p_structure__selected = p_structure;
        break;
    } while (
            (index_of__structure__current =
                (index_of__structure__current+1)
                % ROOM_ENTRANCE_MAX_QUANTITY_OF)
            != index_of__structure__beginning);

    if (!p_structure__selected)
        return 0;

    return p_structure__selected;
}

void initialize_structure_manager(
        Structure_Manager *p_structure_manager) {
    p_structure_manager->quantity_of__allocated_structures = 0;
    p_structure_manager->quantity_of__allocated_rooms = 0;

    for (Index__u32 index_of__room = 0;
            index_of__room < ROOM_MAX_QUANTITY_OF;
            index_of__room++) {
        initialize_room(
                get_p_room_by__index_in__structure_manager(
                    p_structure_manager, 
                    index_of__room));
        p_structure_manager
            ->ptr_array_of__allocated_rooms[index_of__room] = 0;
    }

    for (Index__u32 index_of__structure = 0;
            index_of__structure < STRUCTURE_MAX_QUANTITY_OF;
            index_of__structure++) {
        initialize_structure(
                get_p_structure_by__index_in__structure_manager(
                    p_structure_manager, 
                    index_of__structure));
        p_structure_manager
            ->ptr_array_of__allocated_structures[
                index_of__structure] = 0;
    }
}

Room *allocate_room_in__structure_manager(
        Structure_Manager *p_structure_manager) {
    if (get_quantity_of__rooms_allocated_in__structure_manager(
                p_structure_manager)
            >= STRUCTURE_MAX_QUANTITY_OF) {
        debug_error("allocate_room_in__structure_manager, maximum reached.");
        return 0;
    } 

    Room *p_room =
        find_available_room_in__structure_manager(
                p_structure_manager);

    if (!p_room) {
        debug_error("allocate_room_in__structure_manager, failed to allocate room.");
        return 0;
    }

    p_structure_manager->ptr_array_of__allocated_rooms[
        get_quantity_of__rooms_allocated_in__structure_manager(
                p_structure_manager)] = p_room;

    p_structure_manager->quantity_of__allocated_rooms++;

    return p_room;
}

Structure *allocate_structure_in__structure_manager(
        Structure_Manager *p_structure_manager) {
    if (get_quantity_of__structures_allocated_in__structure_manager(
                p_structure_manager)
            >= STRUCTURE_MAX_QUANTITY_OF) {
        debug_error("allocate_structure_in__structure_manager, maximum reached.");
        return 0;
    } 

    Structure *p_structure =
        find_available_structure_in__structure_manager(
                p_structure_manager);

    if (!p_structure) {
        debug_error("allocate_structure_in__structure_manager, failed to allocate structure.");
        return 0;
    }

    p_structure_manager->ptr_array_of__allocated_structures[
        get_quantity_of__structures_allocated_in__structure_manager(
                p_structure_manager)] = p_structure;

    p_structure_manager->quantity_of__allocated_structures++;

    return p_structure;
}

void release_room_in__structure_manager(
        Structure_Manager *p_structure_manager,
        Room *p_room) {
    Quantity__u32 quantity_of__rooms =
        get_quantity_of__rooms_allocated_in__structure_manager(
                p_structure_manager);
#ifndef NDEBUG
    Index__u32 index =
        p_room
        - p_structure_manager->rooms;
    if (index >= ROOM_MAX_QUANTITY_OF) {
        debug_error("release_room_in__structure_manager, room not allocated with this manager.");
        return;
    }
    if (is_room__allocated(p_room)) {
        debug_error("release_room_in__structure_manager, double free.");
        return;
    }
#endif

    if (quantity_of__rooms == 0) {
        debug_error("release_room_in__structure_manager, double free - manager empty.");
        return;
    }

    set_room_as__deallocated(p_room);

    Room **p_room__last =
        &p_structure_manager
        ->ptr_array_of__allocated_rooms[
            quantity_of__rooms-1];
    for (Index__u32 index_of__room = 0;
            index_of__room < quantity_of__rooms;
            index_of__room++) {
        Room *p_room__comparing =
            p_structure_manager
            ->ptr_array_of__allocated_rooms[index_of__room];

        if (p_room != p_room__comparing)
            continue;

        p_room__comparing =
            *p_room__last;
        *p_room__last = 0;
        return;
    }
}

void release_structure_in__structure_manager(
        Structure_Manager *p_structure_manager,
        Structure *p_structure) {
    Quantity__u32 quantity_of__structures =
        get_quantity_of__structures_allocated_in__structure_manager(
                p_structure_manager);
#ifndef NDEBUG
    Index__u32 index =
        p_structure
        - p_structure_manager->structures;
    if (index >= ROOM_MAX_QUANTITY_OF) {
        debug_error("release_structure_in__structure_manager, structure not allocated with this manager.");
        return;
    }
    if (is_structure__allocated(p_structure)) {
        debug_error("release_structure_in__structure_manager, double free.");
        return;
    }
#endif

    if (quantity_of__structures == 0) {
        debug_error("release_structure_in__structure_manager, double free - manager empty.");
        return;
    }

    set_structure_as__deallocated(p_structure);

    Structure_Ptr_Array_Of__Rooms ptr_array_of__rooms_in__structure;
    get_rooms_in__structure(
            p_structure, 
            ptr_array_of__rooms_in__structure);

    Room **p_ptr_of__room_in__structure =
        ptr_array_of__rooms_in__structure;

    for(Index__u32 index_of__room_in__structure = 0;
            p_ptr_of__room_in__structure
            && index_of__room_in__structure
            < ROOMS_IN_STRUCTURE__MAX_QUANTITY_OF;
            index_of__room_in__structure++) {
        release_room_in__structure_manager(
                p_structure_manager, 
                *p_ptr_of__room_in__structure);
        p_ptr_of__room_in__structure++;
    }

    Structure **p_structure__last =
        &p_structure_manager
        ->ptr_array_of__allocated_structures[
            quantity_of__structures-1];
    for (Index__u32 index_of__structure = 0;
            index_of__structure < quantity_of__structures;
            index_of__structure++) {
        Structure *p_structure__comparing =
            p_structure_manager
            ->ptr_array_of__allocated_structures[index_of__structure];

        if (p_structure != p_structure__comparing)
            continue;

        p_structure__comparing =
            *p_structure__last;
        *p_structure__last = 0;
        return;
    }
}
