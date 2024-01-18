#ifndef WORLD_H
#define WORLD_H

#include <defines.h>

void init_world(World *world);

void add_entity_to__world(
        World *world,
        Entity *entity);

bool poll_world_for__scrolling(
        World *world);

#endif
