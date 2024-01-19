#ifndef GAME_H
#define GAME_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include <defines.h>
#include <world/world.h>

static Entity_Manager inline 
*get_entity_manager_from__game(Game *game) {
    return get_entity_manager_from__world(&game->world);
}

static Chunk_Manager inline 
*get_chunk_manager_from__game(Game *game) {
    return get_chunk_manager_from__world(&game->world);
}

static Collision_Manager inline 
*get_collision_manager_from__game(Game *game) {
    return get_collision_manager_from__world(&game->world);    
}

static PLATFORM_Gfx_Context inline
*get_PLATFORM_gfx_context_from__game(Game *game) {
    return &game->gfx_context;
}

static Input inline
*get_input_from__game(Game *game) {
    return &game->input;
}

static Entity inline
*get_local_player_from__game(Game *game) {
    return game->world.entity_manager.local_player;
}

void init_game(Game *game);

void manage_game(Game *game);

void PLATFORM_pre_render(Game *game);
void PLATFORM_post_render(Game *game);

void manage_game__pre_render(Game *game);
void manage_game__post_render(Game *game);
void manage_entities(Game *game);
void release_entity(Game *game, Entity *entity);

Entity *get_new__player(Game *game, 
        bool is_local_player,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global);
Entity *get_new__entity(Game *game, 
        enum Entity_Kind kind_of_entity,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global);

#endif
