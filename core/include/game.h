#ifndef GAME_H
#define GAME_H

///
/// This entire file is not implemented in core.
/// You will need to compile with a backend.
///

#include <defines.h>

void set_scene_for_game(Game* game, Scene* scene);
void load_config_for_game(Game* game, Config* config);
void load_game(Game* game);
void update_game(Game* game);
void render_game(Game* game);
void unload_game(Game* game);

/// 
/// If returned nullptr, then the current scene 
/// lacks a worldspace.
///
World* get_world_from_game(Game* game);

///
/// If returned nullptr, then the current scene
/// lakcs a worldspace.
///
Entity_Manager* get_entity_manager_from_game(Game* game);

#endif
