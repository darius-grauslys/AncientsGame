#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <defines.h>

void init_collision_manager(
        Collision_Manager *collision_manager);

void poll_collision_mannager(
        Collision_Manager *collision_manager,
        Entity *entity,
        f_entity_collision collision_handler);

void remove_entity_from__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity);

void add_entity_to__collision_manager(
        Collision_Manager *collision_manager,
        Entity *entity);

void update_collision_manager(
        Collision_Manager *collision_manager,
        World *world);

#endif
