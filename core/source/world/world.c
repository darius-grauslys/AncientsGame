#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include <world/world.h>
#include <entity/entity_manager.h>
#include <collisions/collision_manager.h>
#include <world/chunk_manager.h>
#include <world/generators/generator_flat_world.h>
#include <world/generators/generator_test_world.h>
#include <world/world_parameters.h>
#include <game.h>

#include <entity/entity.h>
#include <debug/debug.h>

void initialize_world(World *p_world) {
    initialize_weight_map();
    // initialize_world_parameters(
    //         &world->world_parameters, 
    //         f_chunk_generator__test_world, 
    //         100);
    initialize_world_parameters(
            &p_world->world_parameters, 
            f_chunk_generator__flat_world, 
            100);
    initialize_entity_manager(&p_world->entity_manager);
    initialize_collision_manager(&p_world->collision_manager);
    set_collision_manager__center_chunk(
            &p_world->collision_manager, 
            0, 
            0);
    initialize_chunk_manager(
            &p_world->chunk_manager,
            &p_world->world_parameters);
}

void manage_world(Game *p_game) {
    manage_world__entities(p_game);

    if (poll_world_for__scrolling(&p_game->world)) {
        set_collision_manager__center_chunk(
                &p_game->world.collision_manager,
                p_game->world.chunk_manager.x__center_chunk__signed_index_i32,
                p_game->world.chunk_manager.y__center_chunk__signed_index_i32);
        PLATFORM_update_chunks(
                &p_game->gfx_context,
                &p_game->world.chunk_manager);
    }
}

void manage_world__entities(Game *p_game) {
    World *p_world =
        &p_game->world;
    Entity_Manager *p_entity_manager =
        &p_game->world.entity_manager;

    if (!p_entity_manager->p_local_player) {
        debug_abort("manage_world__entities, p_local_player == 0");
        return;
    }

    Hitbox_AABB *p_player__hitbox =
        &p_entity_manager
        ->p_local_player
        ->hitbox;

    Signed_Index__i32 x__origin = 
        get_global_x_from__hitbox(p_player__hitbox);
    Signed_Index__i32 y__origin = 
        get_global_y_from__hitbox(p_player__hitbox);

    for (Quantity__u16 i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        Entity *p_entity =
            get_p_entity_from__entity_manager(
                    p_entity_manager, i);
        if (!is_entity__enabled(p_entity)) {
            continue;
        }
        if (is_entity__unloaded(p_entity)) {
            release_entity_from__world(p_game, p_entity);
            continue;
        }

        if (p_entity->m_entity_body_handler) {
            p_entity->m_entity_body_handler(p_entity, p_game);
        }

        if (p_entity->m_entity_ai_handler) {
            p_entity->m_entity_ai_handler(p_entity, p_game);
        }

        if (!poll_collision_manager(
                &p_game->world.collision_manager, 
                p_entity)) {
            release_entity_from__world(p_game, p_entity);
            continue;
        }

        if (!poll_chunk_manager_for__tile_collision(
                    &p_world->chunk_manager,
                    p_entity)) {
            release_entity_from__world(p_game, p_entity);
            continue;
        }

        int32_t old_x__chunk, old_y__chunk;
        if (commit_entity_velocity(
                    p_entity, 
                    &old_x__chunk,
                    &old_y__chunk)) {
            remove_entity_from__collision_manager__at(
                    &p_game->world.collision_manager, 
                    p_entity, 
                    old_x__chunk, 
                    old_y__chunk);
            if (!add_entity_to__collision_manager(
                    &p_game->world.collision_manager, 
                    p_entity)) {
                release_entity_from__world(p_game, p_entity);
                continue;
            }
        }

        if (p_entity->m_entity_animation_handler) {
            p_entity->m_entity_animation_handler(
                    p_entity, 
                    &p_game->tick__timer_u32);
        }

        if (!is_entity__hidden(p_entity)) {
            PLATFORM_render_entity(
                    p_entity,
                    x__origin,
                    y__origin,
                    p_game);
        }
    }
}

void add_entity_to__world(
        World *p_world,
        Entity *p_entity) {
    add_entity_to__collision_manager(
            &p_world->collision_manager, 
            p_entity);
}

Entity *allocate_entity_into__world(
        World *p_world,
        enum Entity_Kind the_kind_of_entity,
        Vector__3i32F4 position__3i32F4) {
    Entity *p_entity =
        allocate_entity_in__entity_manager(
                &p_world->entity_manager,
                the_kind_of_entity,
                position__3i32F4);
    add_entity_to__world(
            p_world, 
            p_entity);
    return p_entity;
}

void remove_entity_from__world(
        World *p_world,
        Entity *p_entity) {
    remove_entity_from__collision_manager(
            &p_world->collision_manager,
            p_entity);
}

void release_entity_from__world(
        Game *p_game,
        Entity *p_entity) {
    if (p_entity->m_entity_dispose_handler) {
        p_entity->m_entity_dispose_handler(
                p_entity,
                p_game);
    } else {
        debug_info("release_entity_from__world: %p",
                p_entity);
    }
    release_entity_from__entity_manager(
            get_p_entity_manager_from__game(p_game), 
            p_entity);
}

bool poll_world_for__scrolling(
        World *p_world) {
    bool is_chunks_moved =
        poll_chunk_manager_for__chunk_movement(
            &p_world->chunk_manager,
            &p_world->world_parameters,
            p_world->entity_manager.p_local_player
                ->hitbox.chunk_index__3i32.x__i32,
            p_world->entity_manager.p_local_player
                ->hitbox.chunk_index__3i32.y__i32,
            p_world->entity_manager.p_local_player
                ->hitbox.chunk_index__3i32.z__i32);

    return is_chunks_moved;
}
