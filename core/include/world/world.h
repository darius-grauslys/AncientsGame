#ifndef WORLD_H
#define WORLD_H

#include "collisions/collision_manager.h"
#include "defines_weak.h"
#include "world/chunk_manager.h"
#include <defines.h>

static inline
Camera *get_p_camera_from__world(World *p_world) {
    return &p_world->camera;
}

static inline
Inventory_Manager *get_p_inventory_manager_from__world(World *p_world) {
    return &p_world->inventory_manager;
}

static inline
Item_Manager *get_p_item_manager_from__world(World *p_world) {
    return &p_world->item_manager;
}

static inline
Item_Recipe_Manager *get_p_item_recipe_manager_from__world(World *p_world) {
    return &p_world->item_recipe_manager;
}

static inline
Station_Manager *get_p_station_manager_from__world(World *p_world) {
    return &p_world->station_manager;
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
/// TODO: remove:
///
static inline
Tile *get_p_tile_from__world_using__ray_3i32F20(
        World *p_world,
        Ray__3i32F20 *p_ray__3i32F20) {
    return 0;
}

///
/// TODO: remove:
///
static inline
Entity *get_p_entity_from__world_using__ray_3i32F20(
        World *p_world,
        Ray__3i32F20 *p_ray__3i32F20) {
    return 0;
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

#endif
