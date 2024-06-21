#include <world/camera.h>

void m_camera_handler__default(
        Camera *p_this_camera,
        Game *p_game) {
    Entity *p_local_player =
        p_game->world.entity_manager.p_local_player;
    if (!p_local_player) {
        return;
    }
    set_position_of__camera_to__entity(
            p_this_camera, 
            p_local_player);
}
