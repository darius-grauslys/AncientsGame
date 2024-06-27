#ifndef SCENE__MULTIPLAYER_MENU_H
#define SCENE__MULTIPLAYER_MENU_H

#include <defines.h>

void initialize_scene_as__multiplayer_menu(Scene *p_scene);

void m_load_scene_as__multiplayer_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__multiplayer_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

#endif
