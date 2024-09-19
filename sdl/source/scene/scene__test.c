#include "defines_weak.h"
#include "game.h"

void m_load_scene_as__test_handler(
        Scene *p_this_scene,
        Game *p_game) {
}

void m_enter_scene_handler_as__test(
        Scene *p_this_scene,
        Game *p_game) {

    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
    }
}

void initialize_scene_as__test(Scene *p_scene) {
    p_scene->m_load_scene_handler =
        m_load_scene_as__test_handler;
    p_scene->m_enter_scene_handler =
        m_enter_scene_handler_as__test;
}
