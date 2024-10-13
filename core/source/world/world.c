#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "platform_defines.h"
#include "serialization/serialization_request.h"
#include "serialization/serializer.h"
#include "world/camera.h"
#include "world/chunk_vectors.h"
#include "world/serialization/world_directory.h"
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

void m_serialize_handler__world(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);
void m_deserialize_handler__world(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer);

void initialize_world(
        Game *p_game,
        World *p_world,
        PLATFORM_Graphics_Window 
            *p_PLATFORM_graphics_window_for__world) {

    intialize_serializer(
            &p_world->_serializer, 
            sizeof(World), 
            0, 
            m_serialize_handler__world, 
            m_deserialize_handler__world);

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
            CAMERA_FULCRUM__HEIGHT,
            -BIT(18),
            i32_to__i32F20(100)
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

void teleport_player(
        Game *p_game,
        Vector__3i32F4 position__3i32F4) {
    Chunk_Vector__3i32 chunk_vector__3i32 =
        vector_3i32F4_to__chunk_vector_3i32(
                position__3i32F4);
    remove_entity_from__collision_manager(
            get_p_collision_manager_from__game(p_game), 
            get_p_local_player_from__game(p_game));
    move_chunk_manager_to__chunk_position(
            p_game, 
            get_p_chunk_manager_from__game(p_game), 
            chunk_vector__3i32);
    set_hitbox__position_with__3i32F4(
            &get_p_local_player_from__game(
                p_game)->hitbox,
            position__3i32F4);
    set_collision_manager__center_chunk(
            &p_game->world.collision_manager,
            p_game->world.chunk_manager.x__center_chunk__signed_index_i32,
            p_game->world.chunk_manager.y__center_chunk__signed_index_i32);
    add_entity_to__collision_manager(
            get_p_collision_manager_from__game(p_game), 
            get_p_local_player_from__game(p_game));

    set_position_of__camera_to__entity(
            &get_p_world_from__game(p_game)
            ->camera, 
            get_p_local_player_from__game(p_game));
}

void save_world(
        Game *p_game) {
    save_all_chunks(
            p_game, 
            get_p_chunk_manager_from__game(p_game));

    char path[MAX_LENGTH_OF__IO_PATH];
    stat_world_header_file(
            p_game, 
            path);

    Serialization_Request *p_serialization_request =
        PLATFORM_allocate_serialization_request(
                get_p_PLATFORM_file_system_context_from__game(p_game));

    if (!p_serialization_request) {
        debug_error("save_world, failed to allocated p_serialization_request.");
        return;
    }

    enum PLATFORM_Open_File_Error error =
        PLATFORM_open_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                path, 
                "wb", 
                p_serialization_request);

    if (error) {
        PLATFORM_release_serialization_request(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_serialization_request);
        debug_error("save_world, IO error: %d", error);
        return;
    }
    
    set_serialization_request_as__fire_and_forget(
            p_serialization_request);
    set_serialization_request_as__using_serializer(
            p_serialization_request);
    set_serialization_request_as__write(
            p_serialization_request);
    p_serialization_request->p_serializer =
        &get_p_world_from__game(p_game)->_serializer;
}

void load_world(
        Game *p_game) {
    char path[MAX_LENGTH_OF__IO_PATH];
    Index__u32 index_of__path_append =
        stat_world_header_file(
                p_game, 
                path);
    
    if (!index_of__path_append) {
        debug_error("load_world, failed to stat world header file.");
        return;
    }

    Serialization_Request *p_serialization_request =
        PLATFORM_allocate_serialization_request(
                get_p_PLATFORM_file_system_context_from__game(p_game));

    if (!p_serialization_request) {
        debug_error("load_world, failed to allocated p_serialization_request.");
        return;
    }

    enum PLATFORM_Open_File_Error error =
        PLATFORM_open_file(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                path, 
                "rb", 
                p_serialization_request);

    if (error) {
        PLATFORM_release_serialization_request(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                p_serialization_request);
        debug_error("load_world, IO error: %d", error);
        return;
    }
    
    set_serialization_request_as__fire_and_forget(
            p_serialization_request);
    set_serialization_request_as__using_serializer(
            p_serialization_request);
    set_serialization_request_as__read(
            p_serialization_request);
    p_serialization_request->p_serializer =
        &get_p_world_from__game(p_game)->_serializer;
}

void m_serialize_handler__world(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    World *p_world = get_p_world_from__game(p_game);

    Quantity__u32 length_of__read = WORLD_NAME_MAX_SIZE_OF;
    PLATFORM_write_file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            (u8*)p_world->name, 
            length_of__read, 
            1, 
            p_serialization_request
            ->p_file_handler);

    // TODO: verify the read lengths for errors.
    length_of__read = sizeof(
            p_game->repeatable_pseudo_random.seed__initial);
    PLATFORM_write_file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            (u8*)&p_game->repeatable_pseudo_random.seed__initial, 
            length_of__read, 
            1, 
            p_serialization_request
            ->p_file_handler);

    length_of__read = sizeof(
            p_game->repeatable_pseudo_random.seed__current_random);
    PLATFORM_write_file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            (u8*)&p_game->repeatable_pseudo_random.seed__current_random, 
            length_of__read, 
            1, 
            p_serialization_request
            ->p_file_handler);

    // TODO: save other players if any.
    Entity *p_local_player =
        get_p_local_player_from__game(p_game);

    p_local_player->_serializer.m_serialize_handler(
            p_game,
            p_serialization_request,
            &p_local_player->_serializer);
}

void m_deserialize_handler__world(
        Game *p_game,
        Serialization_Request *p_serialization_request,
        Serializer *p_this_serializer) {
    World *p_world = get_p_world_from__game(p_game);
    Entity *p_entity =
        allocate_entity_into__world(
                p_game, 
                p_world,
                Entity_Kind__Player, 
                VECTOR__3i32F4__0_0_0);

    Quantity__u32 length_of__read = WORLD_NAME_MAX_SIZE_OF;
    PLATFORM_read_file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            (u8*)p_world->name, 
            &length_of__read, 
            1, 
            p_serialization_request
            ->p_file_handler);

    // TODO: verify the read lengths for errors.
    length_of__read = sizeof(
            p_game->repeatable_pseudo_random.seed__initial);
    PLATFORM_read_file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            (u8*)&p_game->repeatable_pseudo_random.seed__initial, 
            &length_of__read, 
            1, 
            p_serialization_request
            ->p_file_handler);

    length_of__read = sizeof(
            p_game->repeatable_pseudo_random.seed__current_random);
    PLATFORM_read_file(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            (u8*)&p_game->repeatable_pseudo_random.seed__current_random, 
            &length_of__read, 
            1, 
            p_serialization_request
            ->p_file_handler);

    if (!p_entity) {
        debug_abort("m_deserialize_handler__world, failed to allocate player.");
        return;
    }

    p_entity->_serializer.m_deserialize_handler(
            p_game,
            p_serialization_request,
            &p_entity->_serializer);
}
