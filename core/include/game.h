#ifndef GAME_H
#define GAME_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include "defines_weak.h"
#include "log/log.h"
#include "log/message.h"
#include "platform.h"
#include "random.h"
#include "timer.h"
#include <defines.h>
#include <world/world.h>

void initialize_game(
        Game *p_game,
        m_Game_Action_Handler m_game_action_handler);
int run_game(Game *p_game);

bool await_game_tick(Game *p_game);

void manage_game(Game *p_game);

void manage_game__pre_render(Game *p_game);
void manage_game__post_render(Game *p_game);

static inline
Quantity__u32 get_ticks_elapsed__game(Game *p_game) {
    return get_time_elapsed_from__timer_u32(&p_game->tick__timer_u32);
}

static inline
Psuedo_Random__i32 get_pseudo_random_i32_from__game(Game *p_game) {
    return get_pseudo_random_i32__intrusively(&p_game->repeatable_pseudo_random);
}

static inline
Psuedo_Random__i32 get_pseudo_random_i32_with__xy_from__game(
        Game *p_game,
        i32 x, i32 y) {
    return get_pseudo_random_i32_with__xy__intrusively(
            &p_game->repeatable_pseudo_random, 
            x, y);
}

static inline
Log *get_p_log__global_from__game(Game *p_game) {
    return &p_game->log__global;
}

static inline
void clear_log__global(Game *p_game) {
    clear_log(get_p_log__global_from__game(p_game));
    PLATFORM_clear_log__global(p_game);
}

static inline
Log *get_p_log__local_from__game(Game *p_game) {
    return &p_game->log__local;
}

static inline
void clear_log__local(Game *p_game) {
    clear_log(get_p_log__local_from__game(p_game));
    PLATFORM_clear_log__local(p_game);
}

static inline
Log *get_p_log__system_from__game(Game *p_game) {
    return &p_game->log__system;
}

bool print_log__global(Game *p_game, char *cstr);
bool print_log__local(Game *p_game, char *cstr);
bool print_log__system(Game *p_game, char *cstr);

static inline
void clear_log__system(Game *p_game) {
    clear_log(get_p_log__system_from__game(p_game));
    PLATFORM_clear_log__system(p_game);
}

static inline 
World *get_p_world_from__game(Game *p_game) {
    return &p_game->world;
}

static inline 
Sprite_Gfx_Allocation_Manager *get_p_sprite_gfx_allocation_manager_from__game(
        Game *p_game) {
    return &p_game->sprite_gfx_allocation_manager;
}

static inline 
Aliased_Texture_Manager *get_p_aliased_texture_manager_from__game(Game *p_game) {
    return &p_game->aliased_texture_manager;
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

static inline
Inventory_Manager *get_p_inventory_manager_from__game(Game *p_game) {
    return &p_game->inventory_manager;
}

static inline
Item_Manager *get_p_item_manager_from__game(Game *p_game) {
    return &p_game->item_manager;
}

static inline
Item_Recipe_Manager *get_p_item_recipe_manager_from__game(Game *p_game) {
    return &p_game->item_recipe_manager;
}

static inline
Station_Manager *get_p_station_manager_from__game(Game *p_game) {
    return &p_game->station_manager;
}

static inline 
Scene_Manager *get_p_scene_manager_from__game(Game *p_game) {
    return &p_game->scene_manager;
}

static inline 
Entity_Manager *get_p_entity_manager_from__game(Game *p_game) {
    return get_p_entity_manager_from__world(&p_game->world);
}

static inline 
Chunk_Manager *get_p_chunk_manager_from__game(Game *p_game) {
    return get_p_chunk_manager_from__world(&p_game->world);
}

static inline
World_Parameters *get_p_world_parameters_from__game(Game *p_game) {
    return get_p_world_parameters_from__world(
            get_p_world_from__game(p_game));
}

static inline 
Collision_Manager *get_p_collision_manager_from__game(Game *p_game) {
    return get_p_collision_manager_from__world(&p_game->world);    
}

static inline
PLATFORM_File_System_Context *get_p_PLATFORM_file_system_context_from__game(
        Game *p_game) {
    return p_game->p_PLATFORM_file_system_context;
}

static inline
PLATFORM_Audio_Context *get_p_PLATFORM_audio_context_from__game(
        Game *p_game) {
    return p_game->p_PLATFORM_audio_context;
}

static inline
PLATFORM_Gfx_Context *get_p_PLATFORM_gfx_context_from__game(Game *p_game) {
    return p_game->gfx_context.p_PLATFORM_gfx_context;
}

static inline
Input *get_p_input_from__game(Game *p_game) {
    return &p_game->input;
}

static inline
Entity *get_p_local_player_from__game(Game *p_game) {
    return get_p_local_player_from__world(&p_game->world);
}

#endif
