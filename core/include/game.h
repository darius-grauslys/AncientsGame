#ifndef GAME_H
#define GAME_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include <defines.h>
#include <world/world.h>

static Entity_Manager inline 
*get_entity_manager_ptr_from__game(Game *p_game) {
    return get_entity_manager_ptr_from__world(&p_game->world);
}

static Chunk_Manager inline 
*get_chunk_manager_ptr_from__game(Game *p_game) {
    return get_chunk_manager_ptr_from__world(&p_game->world);
}

static Collision_Manager inline 
*get_collision_manager_ptr_from__game(Game *p_game) {
    return get_collision_manager_ptr_from__world(&p_game->world);    
}

static PLATFORM_Gfx_Context inline
*get_PLATFORM_gfx_context_ptr_from__game(Game *p_game) {
    return &p_game->gfx_context;
}

static Input inline
*get_input_ptr_from__game(Game *p_game) {
    return &p_game->input;
}

static Entity inline
*get_local_player_ptr_from__game(Game *p_game) {
    return get_local_player_ptr_from__world(&p_game->world);
}

void init_game(Game *p_game);

void manage_game(Game *p_game);

void manage_game__pre_render(Game *p_game);
void manage_game__post_render(Game *p_game);
void manage_entities(Game *p_game);
void release_entity(Game *p_game, Entity *p_entity);

Entity *get_new__player(Game *p_game, 
        bool is_local_player,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global);
Entity *get_new__entity(Game *p_game, 
        enum Entity_Kind kind_of_entity,
        int32_t x__global,
        int32_t y__global,
        int32_t z__global);

#endif
