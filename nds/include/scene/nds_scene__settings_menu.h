#ifndef SCENE__SETTINGS_MENU_H
#define SCENE__SETTINGS_MENU_H

#include <defines.h>

void initialize_scene_as__settings_menu(Scene *p_scene);

void m_load_scene_as__settings_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

void m_unload_scene_as__settings_menu_handler(
        Scene *p_this_scene,
        Game *p_game);

#endif
