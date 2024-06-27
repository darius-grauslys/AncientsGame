#ifndef GAME_H
#define GAME_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include <defines.h>
#include <world/world.h>

static inline
Camera *get_p_camera_from__game(Game *p_game) {
    return get_p_camera_from__world(&p_game->world);
}

static Entity_Manager inline 
*get_p_entity_manager_from__game(Game *p_game) {
    return get_p_entity_manager_from__world(&p_game->world);
}

static Chunk_Manager inline 
*get_p_chunk_manager_from__game(Game *p_game) {
    return get_p_chunk_manager_from__world(&p_game->world);
}

static Collision_Manager inline 
*get_p_collision_manager_from__game(Game *p_game) {
    return get_p_collision_manager_from__world(&p_game->world);    
}

static PLATFORM_Gfx_Context inline
*get_p_PLATFORM_gfx_context_from__game(Game *p_game) {
    return &p_game->gfx_context;
}

static Input inline
*get_p_input_from__game(Game *p_game) {
    return &p_game->input;
}

static UI_Manager inline
*get_p_ui_manager_from__game(Game *p_game) {
    return &p_game->ui_manager;
}

static Entity inline
*get_p_local_player_from__game(Game *p_game) {
    return get_p_local_player_from__world(&p_game->world);
}

void initialize_game(
        Game *p_game,
        m_Game_Action_Handler m_game_action_handler);
int run_game(Game *p_game);

void manage_game(Game *p_game);

void manage_game__pre_render(Game *p_game);
void manage_game__post_render(Game *p_game);

#endif
