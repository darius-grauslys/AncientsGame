#ifndef WORLD_H
#define WORLD_H

#include <defines.h>

static inline
Camera *get_p_camera_from__world(World *p_world) {
    return &p_world->camera;
}

static Entity_Manager inline 
*get_p_entity_manager_from__world(World *p_world) {
    return &p_world->entity_manager;
}

static Chunk_Manager inline 
*get_p_chunk_manager_from__world(World *p_world) {
    return &p_world->chunk_manager;
}

static Collision_Manager inline 
*get_p_collision_manager_from__world(World *p_world) {
    return &p_world->collision_manager;
}

static World_Parameters inline
*get_p_world_parameters_from__world(World *p_world) {
    return &p_world->world_parameters;
}

static Entity inline
*get_p_local_player_from__world(World *p_world) {
    return p_world->entity_manager.p_local_player;
}

void initialize_world(World *p_world);
void manage_world(Game *p_game);
void manage_world__entities(Game *p_game);

void add_entity_to__world(
        World *p_world,
        Entity *p_entity);

Entity *allocate_entity_into__world(
        World *p_world,
        enum Entity_Kind the_kind_of_entity,
        Vector__3i32F4 position__3i32F4);

void remove_entity_from__world(
        World *p_world,
        Entity *p_entity);

void release_entity_from__world(
        Game *p_game,
        Entity *p_entity);

bool poll_world_for__scrolling(
        World *p_world);

#endif
