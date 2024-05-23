#ifndef WORLD_H
#define WORLD_H

#include <defines.h>

static Entity_Manager inline 
*get_entity_manager_from__world(World *world) {
    return &world->entity_manager;
}

static Chunk_Manager inline 
*get_chunk_manager_from__world(World *world) {
    return &world->chunk_manager;
}

static Collision_Manager inline 
*get_collision_manager_from__world(World *world) {
    return &world->collision_manager;
}

static World_Parameters inline
*get_world_parameters_from__world(World *world) {
    return &world->world_parameters;
}

void init_world(World *world);

void add_entity_to__world(
        World *world,
        Entity *entity);

bool poll_world_for__scrolling(
        World *world);

#endif
