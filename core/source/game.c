#include <game.h>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <debug/debug.h>
#include <input/input.h>
#include <world/chunk_manager.h>
#include <rendering/gfx_context.h>
#include <rendering/animate_entity.h>
#include <rendering/render_entity.h>
#include <world/world.h>

#include <entity/controllers/collidable_entity_handlers.h>
#include <entity/controllers/entity_handlers.h>
#include <entity/controllers/controller_player.h>
#include <entity/controllers/controller_dummy.h>
#include <entity/controllers/humanoid_animation_handler.h>

#include <collisions/hitbox_aabb.h>
#include <collisions/collision_manager.h>

#include <world/chunk.h>
#include <world/tile.h>

void init_game(Game *p_game) {
    PLATFORM_init_gfx_context(&p_game->gfx_context);
    //TODO: start with a main menu.
    PLATFORM_init_rendering__game(&p_game->gfx_context);

    init_world(&p_game->world);

    // TODO: prob wanna remove some of the stuff below

    get_new__player(p_game, true,
            0, 0, 0);

    move_chunk_manager(
            &p_game->world.chunk_manager, 
            &p_game->world.world_parameters, 
            DIRECTION__NORTH_WEST,
            2);

    PLATFORM_update_chunks(
            &p_game->gfx_context,
            &p_game->world.chunk_manager);
}

void manage_game(Game *p_game) {
    manage_game__pre_render(p_game);
    manage_game__post_render(p_game);
    p_game->tick__timer_u32++;
}

void manage_game__pre_render(Game *p_game) {
    PLATFORM_pre_render(p_game);
}

void manage_game__post_render(Game *p_game) {
    PLATFORM_poll_input(p_game);
    manage_entities(p_game);

    if (poll_world_for__scrolling(&p_game->world)) {
        set_collision_manager__center_chunk(
                &p_game->world.collision_manager,
                p_game->world.chunk_manager.x__center_chunk__signed_index_i32,
                p_game->world.chunk_manager.y__center_chunk__signed_index_i32);
        PLATFORM_update_chunks(
                &p_game->gfx_context,
                &p_game->world.chunk_manager);
    }

    PLATFORM_post_render(p_game);
}

void manage_entities(Game *p_game) {
    Entity_Manager *p_entity_manager =
        get_entity_manager_ptr_from__game(p_game);

    Hitbox_AABB *p_player__hitbox =
        &p_game
        ->world
        .entity_manager
        .p_local_player
        ->hitbox;

    Signed_Index__i32 x__origin = 
        get_global_x_from__hitbox(p_player__hitbox);
    Signed_Index__i32 y__origin = 
        get_global_y_from__hitbox(p_player__hitbox);

    for (Quantity__u16 i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        Entity *p_entity =
            get_entity_ptr_from__entity_manager(
                    p_entity_manager, i);
        if (!is_entity__enabled(p_entity)) {
            continue;
        }
        if (is_entity__unloaded(p_entity)) {
            release_entity(p_game, p_entity);
            continue;
        }

        if (p_entity->m_controller_handler) {
            p_entity->m_controller_handler(p_entity, p_game);
        }

        if (!poll_collision_manager(
                &p_game->world.collision_manager, 
                p_entity)) {
            release_entity(p_game, p_entity);
            continue;
        }

        if (!poll_chunk_manager_for__tile_collision(
                    &p_game->world.chunk_manager,
                    p_entity)) {
            release_entity(p_game, p_entity);
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
                release_entity(p_game, p_entity);
                continue;
            }
        }

        if (p_entity->m_animation_handler) {
            p_entity->m_animation_handler(
                    p_entity, 
                    p_game->tick__timer_u32);
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

void release_entity(Game *p_game, Entity *p_entity) {
    if (p_entity->m_dispose_handler) {
        p_entity->m_dispose_handler(p_entity, p_game);
        debug_info("released entity with disposer.");
    } else {
        debug_info("released entity.");
    }
    release_entity__silently(
            &p_game->world.entity_manager,
            p_entity);
}

Entity *get_new__humanoid(Game *p_game, 
        enum Entity_Kind kind_of_entity,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    Entity *p_entity = allocate__entity(
            &p_game->world.entity_manager, kind_of_entity);

    if (!p_entity) {
        return 0;
    }

    init_hitbox(
            &p_entity->hitbox, 
            6, 6, 
            x__global, 
            y__global, 
            z__global);

    set_entity__collider(
            p_entity, 
            m_entity_collision_handler);
    set_entity__tile_collider(
            p_entity,
            m_entity_tile_collision_handler);
    set_entity__animator(
            p_entity,
            m_humanoid_animation_handler);

    add_entity_to__collision_manager(
            &p_game->world.collision_manager, p_entity);

    return p_entity;
}

Entity *get_new__player(Game *p_game, 
        bool is_local_player,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    Entity *p_player = get_new__humanoid(
            p_game, 
            Entity_Kind__Player,
            x__global,
            y__global,
            z__global);
    if (!p_player) {
        return 0;
    }
    if (is_local_player) {
        Entity_Manager *p_entity_manager = 
            get_entity_manager_ptr_from__game(p_game);
        p_entity_manager->p_local_player = p_player;
        set_entity__is_not_updating_position(
                p_player);
        set_entity__controller(
                p_player,
                m_controller_for__player);
    }

    return p_player;
}

Entity *get_new__entity(Game *p_game, 
        enum Entity_Kind kind_of_entity,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    switch (kind_of_entity) {
        default:
            ///
            /// If you're trying to make a player,
            /// call get_new__player instead.
            ///
            debug_error("Failed to get new entity, \
invalid kind_of_entity. get_new__entity(...).");
            break;
        // non-player humanoids:
        case Entity_Kind__Skeleton:
        case Entity_Kind__Zombie:
            return get_new__humanoid(
                    p_game,
                    kind_of_entity,
                    x__global,
                    y__global,
                    z__global);
    }

    return 0;
}
