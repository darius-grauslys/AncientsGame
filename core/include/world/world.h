#ifndef WORLD_H
#define WORLD_H

#include "collisions/collision_manager.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "world/chunk_manager.h"
#include <defines.h>

static inline
Camera *get_p_camera_from__world(World *p_world) {
    return &p_world->camera;
}

static inline 
Entity_Manager *get_p_entity_manager_from__world(World *p_world) {
    return &p_world->entity_manager;
}

static inline 
Chunk_Manager *get_p_chunk_manager_from__world(World *p_world) {
    return &p_world->chunk_manager;
}

static inline
Tile_Logic_Manager *get_p_tile_logic_manager_from__world(World *p_world) {
    return &p_world->tile_logic_manager;
}

static inline
Collision_Manager *get_p_collision_manager_from__world(World *p_world) {
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

///
/// Returns tile ptr if ray is on a tile
/// otherwise returns nullptr.
///
static inline
Tile *get_p_tile_from__world_using__ray_3i32F20(
        World *p_world,
        Ray__3i32F20 *p_ray__3i32F20) {
    return get_p_tile_from__chunk_manager_with__ray_3i32F20(
            get_p_chunk_manager_from__world(p_world),
            p_ray__3i32F20);
}

///
/// Returns entity ptr if ray is on entity
/// otherwise returns nullptr.
///
static inline
Entity *get_p_entity_from__world_using__ray_3i32F20(
        World *p_world,
        Ray__3i32F20 *p_ray__3i32F20) {
    return get_p_entity_from__collision_manager_with__ray_3i32F20(
            get_p_collision_manager_from__world(p_world),
            p_ray__3i32F20);
}

static inline
Entity *get_p_entity_from__world_using__3i32F4(
        World *p_world,
        Vector__3i32F4 position__3i32F4) {
    return get_p_entity_from__collision_manager_with__3i32F4(
            get_p_collision_manager_from__world(p_world), 
            position__3i32F4);
}

void initialize_world(
        Game *p_game,
        World *p_world,
        PLATFORM_Graphics_Window 
            *p_PLATFORM_graphics_window_for__world);
void manage_world(Game *p_game);
void manage_world__entities(Game *p_game);

void add_entity_to__world(
        World *p_world,
        Entity *p_entity);

Entity *allocate_entity_into__world(
        Game *p_game,
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
        Game *p_game,
        World *p_world);

void teleport_player(
        Game *p_game,
        Vector__3i32F4 position__3i32F4);

static inline
Tile *get_p_tile_thats__infront_of_this__entity(
        World *p_world,
        Entity *p_entity) {
    return
        get_p_tile_from__chunk_manager_with__3i32F4(
                get_p_chunk_manager_from__world(p_world),
                get_vector_3i32F4_thats__infront_of_this__entity(
                    p_entity));
}

static inline
Tile *get_p_tile_and_vector_3i32F4_thats__infront_of_this__entity(
        World *p_world,
        Entity *p_entity,
        Vector__3i32F4 *p_vector__3i32F4) {
    *p_vector__3i32F4 =
        get_vector_3i32F4_thats__infront_of_this__entity(
                p_entity);
    return get_p_tile_from__chunk_manager_with__3i32F4(
            get_p_chunk_manager_from__world(p_world), 
            *p_vector__3i32F4);
}

#endif
