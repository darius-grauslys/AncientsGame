#ifndef ROOM_H
#define ROOM_H

#include "defines_weak.h"
#include <defines.h>

void inititalize_room(
        Room *p_room);

Vector__3i32F4 get_closest_entrance_to__room(
        Room *p_room,
        Vector__3i32F4 position);

#endif
