#include <game.h>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <debug/debug.h>
#include <input/input.h>
#include <world/chunk_manager.h>
#include <rendering/gfx_context.h>
#include <rendering/animate_entity.h>
#include <rendering/render_entity.h>

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

    bool is_chunks_moved =
        poll_chunk_manager__for_chunk_movement(
            &game->chunk_manager,
            &game->world_params,
            game->local_player->x__chunk,
            game->local_player->y__chunk);
    if (is_chunks_moved) {
        PLATFORM_update_chunks(
                &game->gfx_context,
                &game->chunk_manager);
    }

    PLATFORM_post_render(game);
}

void manage_entities(Game *game) {
    Entity_Manager *entity_manager =
        &game->entity_manager;

    for (uint32_t i=0;
            i<ENTITY_MAXIMUM__QUANTITY_OF;i++) {
        Entity *entity =
            &game->entity_manager.entities[i];
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
            &game->entity_manager,
            entity);
}
