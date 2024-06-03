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

void initialize_game(
        Game *p_game,
        m_Game_Action_Handler m_game_action_handler);
int run_game(Game *p_game);

void manage_game(Game *p_game);

void manage_game__pre_render(Game *p_game);
void manage_game__post_render(Game *p_game);

#endif
