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
#include <world/viewing_fulcrum.h>

#include <entity/controllers/collidable_entity_handlers.h>
#include <entity/controllers/entity_handlers.h>
#include <entity/controllers/controller_player.h>
#include <entity/controllers/controller_dummy.h>

#include <collisions/hitbox_aabb.h>
#include <collisions/collision_manager.h>

void init_game(Game *game) {
    PLATFORM_init_gfx_context(&game->gfx_context);
    //TODO: start with a main menu.
    PLATFORM_init_rendering__game(&game->gfx_context);

    init_world(&game->world);

    // TODO: prob wanna remove some of the stuff below

    get_new__player(game, true,
            0, 0, 0);

    Tile tile;
    init_tile(
            &tile,
            Tile_Kind__Amethyst);
    Chunk *chunk =
        get_chunk_from__chunk_manager(
            &game->world.chunk_manager, 
            0, -2, 0);
    set_tile_of__chunk(
            chunk,
            5, 5, 5,
            &tile);

    PLATFORM_update_chunks(
            &game->gfx_context,
            &game->world.chunk_manager,
            &game->world.viewing_fulcrum);
}

void manage_game(Game *game) {
    manage_game__pre_render(game);
    manage_game__post_render(game);
    game->tick++;
}

void manage_game__pre_render(Game *game) {
    PLATFORM_pre_render(game);
}

void manage_game__post_render(Game *game) {
    PLATFORM_poll_input(game);
    manage_entities(game);

    focus_viewing_fulcrum_at__entity(
            &game->world.viewing_fulcrum, 
            get_local_player_from__game(game));

    if (poll_world_for__scrolling(&game->world)) {
        set_collision_manager__center_chunk(
                &game->world.collision_manager,
                game->world.chunk_manager.x__center_chunk,
                game->world.chunk_manager.y__center_chunk);
        PLATFORM_update_chunks(
                &game->gfx_context,
                &game->world.chunk_manager,
                &game->world.viewing_fulcrum);
    }

    PLATFORM_post_render(game);
}

void manage_entities(Game *game) {
    Entity_Manager *entity_manager =
        &game->world.entity_manager;

    for (uint32_t i=0;
            i<ENTITY_MAXIMUM_QUANTITY_OF;i++) {
        Entity *entity =
            &game->world.entity_manager.entities[i];
        if (!is_entity__enabled(entity)) {
            continue;
        }
        if (is_entity__unloaded(entity)) {
            release_entity(game, entity);
            continue;
        }

        if (entity->controller_handler) {
            entity->controller_handler(entity, game);
        }

        if (!poll_collision_manager(
                &game->world.collision_manager, 
                entity)) {
            release_entity(game, entity);
            continue;
        }

        int32_t old_x__chunk, old_y__chunk;
        if (commit_entity_velocity(entity, 
                    &old_x__chunk,
                    &old_y__chunk)) {
            remove_entity_from__collision_manager__at(
                    &game->world.collision_manager, 
                    entity, 
                    old_x__chunk, 
                    old_y__chunk);
            if (!add_entity_to__collision_manager(
                    &game->world.collision_manager, 
                    entity)) {
                release_entity(game, entity);
                continue;
            }
        }

        //TODO: remove magic number, 8
        if (game->tick % 8 == 0) {
            animate_entity(entity);
            PLATFORM_render_entity(entity, game);
        }
    }
}

void release_entity(Game *game, Entity *entity) {
    if (entity->dispose_handler) {
        entity->dispose_handler(entity, game);
        debug_info("released entity with disposer.");
    } else {
        debug_info("released entity.");
    }
    release_entity__silently(
            &game->world.entity_manager,
            entity);
}

Entity *get_new__humanoid(Game *game, 
        enum Entity_Kind kind_of_entity,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    Entity *entity = allocate__entity(
            &game->world.entity_manager, kind_of_entity);

    if (!entity) {
        return 0;
    }

    init_hitbox(
            &entity->hitbox, 
            8, 8, 
            x__global, 
            y__global, 
            z__global);

    set_entity__collider(
            entity, 
            m_entity_collision_handler);

    add_entity_to__collision_manager(
            &game->world.collision_manager, entity);

    return entity;
}

Entity *get_new__player(Game *game, 
        bool is_local_player,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global) {
    Entity *player = get_new__humanoid(
            game, 
            Entity_Kind__Player,
            x__global,
            y__global,
            z__global);
    if (!player) {
        return 0;
    }
    if (is_local_player) {
        Entity_Manager *entity_manager = 
            &game->world.entity_manager;
        entity_manager->local_player = player;
        set_entity__is_not_updating_position(
                player);
        set_entity__controller(
                player,
                m_controller_for__player);
    }

    return player;
}

Entity *get_new__entity(Game *game, 
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
                    game,
                    kind_of_entity,
                    x__global,
                    y__global,
                    z__global);
    }

    return 0;
}
