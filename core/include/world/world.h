#ifndef WORLD_H
#define WORLD_H

#include <defines.h>

static Entity_Manager inline 
*get_entity_manager_ptr_from__world(World *p_world) {
    return &p_world->entity_manager;
}

static Chunk_Manager inline 
*get_chunk_manager_ptr_from__world(World *p_world) {
    return &p_world->chunk_manager;
}

static Collision_Manager inline 
*get_collision_manager_ptr_from__world(World *p_world) {
    return &p_world->collision_manager;
}

static World_Parameters inline
*get_world_parameters_ptr_from__world(World *p_world) {
    return &p_world->world_parameters;
}

static Entity inline
*get_local_player_ptr_from__world(World *p_world) {
    return p_world->entity_manager.p_local_player;
}

void init_world(World *p_world);

void add_entity_to__world(
        World *p_world,
        Entity *p_entity);

bool poll_world_for__scrolling(
        World *p_world);

#endif
