#include <world/world.h>
#include <entity/entity_manager.h>
#include <collisions/collision_manager.h>
#include <world/chunk_manager.h>
#include <world/generators/generator_flat_world.h>
#include <world/generators/generator_test_world.h>
#include <world/world_parameters.h>

// temp:
#include <entity/controllers/controller_player.h>
#include <entity/controllers/controller_dummy.h>
#include <entity/entity.h>
#include <rendering/rendering.h>
#include <debug/debug.h>

void init_world(World *p_world) {
    init_weight_map();
    // init_world_parameters(
    //         &world->world_parameters, 
    //         f_chunk_generator__test_world, 
    //         100);
    init_world_parameters(
            &p_world->world_parameters, 
            f_chunk_generator__flat_world, 
            100);
    init_entity_manager(&p_world->entity_manager);
    init_collision_manager(&p_world->collision_manager);
    set_collision_manager__center_chunk(
            &p_world->collision_manager, 
            0, 
            0);
    init_chunk_manager(
            &p_world->chunk_manager,
            &p_world->world_parameters);
}

void add_entity_to__world(
        World *p_world,
        Entity *p_entity) {
    add_entity_to__collision_manager(
            &p_world->collision_manager, 
            p_entity);
}

bool poll_world_for__scrolling(
        World *p_world) {
    bool is_chunks_moved =
        poll_chunk_manager_for__chunk_movement(
            &p_world->chunk_manager,
            &p_world->world_parameters,
            p_world->entity_manager.p_local_player
                ->hitbox.x__chunk__signed_index_i32,
            p_world->entity_manager.p_local_player
                ->hitbox.y__chunk__signed_index_i32,
            p_world->entity_manager.p_local_player
                ->hitbox.z__chunk__signed_index_i32);

    return is_chunks_moved;
}
