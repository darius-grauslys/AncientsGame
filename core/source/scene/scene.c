#include <scene/scene.h>
#include <game.h>

void m_enter_scene_handler__default(
        Scene *p_this_scene,
        Game *p_game) {
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game(p_game);
    }
}
