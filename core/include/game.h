#ifndef GAME_H
#define GAME_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include "timer.h"
#include <defines.h>
#include <world/world.h>

static inline
Quantity__u32 get_time_elapsed__game(Game *p_game) {
    return get_time_elapsed_from__timer_u32(&p_game->tick__timer_u32);
}

static inline
Camera *get_p_camera_from__game(Game *p_game) {
    return get_p_camera_from__world(&p_game->world);
}

static inline
Process_Manager *get_p_process_manager_from__game(Game *p_game) {
    return &p_game->process_manager;
}

static inline
Sort_List_Manager *get_p_sort_list_manager_from__game(Game *p_game) {
    return &p_game->sort_list_manager;
}

static inline
Path_List_Manager *get_p_path_list_manager_from__game(Game *p_game) {
    return &p_game->path_list_manager;
}

static Entity_Manager inline 
*get_p_entity_manager_from__game(Game *p_game) {
    return get_p_entity_manager_from__world(&p_game->world);
}

static Chunk_Manager inline 
*get_p_chunk_manager_from__game(Game *p_game) {
    return get_p_chunk_manager_from__world(&p_game->world);
}

static World inline 
*get_p_world_from__game(Game *p_game) {
    return &p_game->world;
}

static Collision_Manager inline 
*get_p_collision_manager_from__game(Game *p_game) {
    return get_p_collision_manager_from__world(&p_game->world);    
}

static PLATFORM_Gfx_Context inline
*get_p_PLATFORM_gfx_context_from__game(Game *p_game) {
    return p_game->p_gfx_context;
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
