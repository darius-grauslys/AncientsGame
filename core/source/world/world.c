#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "world/camera.h"
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
#include <vectors.h>

void initialize_world(
        Game *p_game,
        World *p_world,
        PLATFORM_Graphics_Window 
            *p_PLATFORM_graphics_window_for__world) {
    // TODO: take world name in by world_parameters
    strncpy(p_world->name, "default_world", WORLD_NAME_MAX_SIZE_OF);
    p_world->length_of__world_name = strnlen(p_world->name, WORLD_NAME_MAX_SIZE_OF);

    p_world->p_PLATFORM_graphics_window_for__world =
        p_PLATFORM_graphics_window_for__world;
    // TODO: modularize this better:
    initialize_weight_map();
    // initialize_world_parameters(
    //         &p_world->world_parameters, 
    //         f_chunk_generator__test_world);
    initialize_world_parameters(
            &p_world->world_parameters, 
            f_chunk_generator__flat_world);
    initialize_entity_manager(&p_world->entity_manager);
    initialize_collision_manager(&p_world->collision_manager);
    set_collision_manager__center_chunk(
            &p_world->collision_manager, 
            0, 
            0);
    initialize_chunk_manager(
            p_game,
            &p_world->chunk_manager);
    initialize_camera(
            &p_world->camera,
            get_vector__3i32F4_using__i32(
                0, 0, 0),
            0, //nullptr handler
            CAMERA_FULCRUM__WIDTH,
            CAMERA_FULCRUM__HEIGHT
            );
}

void manage_world(Game *p_game) {
    if (poll_chunk_manager_for__serialization(
                p_game, 
                get_p_chunk_manager_from__game(p_game))) {
        return;
    }
    manage_world__entities(p_game);

    if (p_game->world.camera.m_camera_handler) {
        p_game->world.camera.m_camera_handler(
                &p_game->world.camera,
                p_game);
    }

    if (poll_world_for__scrolling(p_game, &p_game->world)) {
        set_collision_manager__center_chunk(
                &p_game->world.collision_manager,
                p_game->world.chunk_manager.x__center_chunk__signed_index_i32,
                p_game->world.chunk_manager.y__center_chunk__signed_index_i32);
        PLATFORM_update_chunks(
                get_p_PLATFORM_gfx_context_from__game(p_game),
                get_p_chunk_manager_from__game(p_game));
    }
}

void manage_world__entities(Game *p_game) {
    World *p_world =
        &p_game->world;
    Entity_Manager *p_entity_manager =
        &p_game->world.entity_manager;

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

        //TODO: only do this for entities which
        //are polling for collisions
        if (!poll_collision_manager(
                &p_game->world.collision_manager, 
                p_game,
                p_entity,
                p_entity->m_entity_collision_handler)) {
            debug_info__verbose("!poll_collision_manager, release entity");
            release_entity_from__world(p_game, p_entity);
            continue;
        }

        //TODO: only do this for entities which
        //are polling for collisions
        if (!poll_chunk_manager_for__tile_collision(
                    &p_world->chunk_manager,
                    p_entity)) {
            debug_info__verbose("!poll_chunk_manager_for__tile_collision, release entity");
            release_entity_from__world(p_game, p_entity);
            continue;
        }

        Chunk_Vector__3i32 old_chunk_vector =
            vector_3i32F4_to__chunk_vector_3i32(
                    p_entity->hitbox.position__3i32F4);

        commit_hitbox_velocity(&p_entity->hitbox);

        //TODO: only do this for entities which
        //are polling for collisions
        Chunk_Vector__3i32 new_chunk_vector =
            vector_3i32F4_to__chunk_vector_3i32(
                    p_entity->hitbox.position__3i32F4);
        if (!is_chunk_vectors_3i32__equal(
                    old_chunk_vector, new_chunk_vector)) {
            remove_entity_from__collision_manager__at(
                    &p_game->world.collision_manager, 
                    p_entity, 
                    old_chunk_vector);
            if (!add_entity_to__collision_manager(
                    &p_game->world.collision_manager, 
                    p_entity)) {
                release_entity_from__world(p_game, p_entity);
                continue;
            }
        }

        if (p_entity->m_entity_animation_handler) {
            p_entity->m_entity_animation_handler(
                    p_entity);
        }

        PLATFORM_render_entity(
                p_entity,
                p_game);
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
        Game *p_game,
        World *p_world,
        enum Entity_Kind the_kind_of_entity,
        Vector__3i32F4 position__3i32F4) {
    Entity *p_entity =
        allocate_entity_in__entity_manager(
                p_game,
                get_p_entity_manager_from__world(p_world),
                the_kind_of_entity,
                position__3i32F4,
                p_world->p_PLATFORM_graphics_window_for__world);
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
    }
    remove_entity_from__world(
            get_p_world_from__game(p_game), 
            p_entity);
    release_entity_from__entity_manager(
            get_p_entity_manager_from__game(p_game), 
            p_entity);
}

bool poll_world_for__scrolling(
        Game *p_game,
        World *p_world) {
    bool is_chunks_moved =
        poll_chunk_manager_for__chunk_movement(
                p_game,
                &p_world->chunk_manager,
                p_world->camera.position);

    return is_chunks_moved;
}
