#include <world/world.h>
#include <entity/entity_manager.h>
#include <collisions/collision_manager.h>
#include <world/chunk_manager.h>
#include <world/generators/generator_flat_world.h>
#include <world/world_parameters.h>
#include <world/viewing_fulcrum.h>

// temp:
#include <entity/controllers/controller_player.h>
#include <entity/controllers/controller_dummy.h>
#include <entity/entity.h>
#include <rendering/rendering.h>
#include <debug/debug.h>

void init_world(World *world) {
    init_weight_map();
    init_world_parameters(&world->world_params, 
            chunk_generator__flat_world_f, 0);
    init_entity_manager(&world->entity_manager);
    init_collision_manager(&world->collision_manager);
    set_collision_manager__center_chunk(
            &world->collision_manager, 0, 0);
    init_chunk_manager(
            &world->chunk_manager,
            &world->world_params);
    init_viewing_fulcrum(&world->viewing_fulcrum);
}

void add_entity_to__world(
        World *world,
        Entity *entity) {
    add_entity_to__collision_manager(
            &world->collision_manager, 
            entity);
}

bool poll_world_for__scrolling(
        World *world) {
    bool is_chunks_moved =
        poll_chunk_manager_for__chunk_movement(
            &world->chunk_manager,
            &world->world_params,
            world->viewing_fulcrum.fulcrum.x__chunk,
            world->viewing_fulcrum.fulcrum.y__chunk,
            world->viewing_fulcrum.fulcrum.z__chunk);

    return is_chunks_moved;
}
