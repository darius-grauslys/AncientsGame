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

void init_game(Game *game) {
    PLATFORM_init_gfx_context(&game->gfx_context);
    //TODO: start with a main menu.
    PLATFORM_init_rendering__game(&game->gfx_context);

    init_world(&game->world);

    move_chunk_manager__chunks(
            &game->world.chunk_manager, 
            &game->world.world_params, 
            DIRECTION__NORTH,
            2);
    PLATFORM_update_chunks(
            &game->gfx_context,
            &game->world.chunk_manager);
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

    if (poll_world_for__scrolling(&game->world)) {
        PLATFORM_update_chunks(
                &game->gfx_context,
                &game->world.chunk_manager);
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

        if (entity->controller_handler) {
            entity->controller_handler(entity, game);
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
