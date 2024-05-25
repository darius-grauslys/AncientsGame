#ifndef SCENE__GAME_H
#define SCENE__GAME_H

#include <defines.h>

void init_scene_as__game(Scene *p_scene);

void m_load_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__game_handler(
        Scene *p_this_scene,
        Game *p_game);

#endif
