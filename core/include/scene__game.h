#ifndef SCENE__GAME_H
#define SCENE__GAME_H

#include <defines.h>

static inline
Timer__u8 *get_hud_timer_from__scene__game(
        Scene *p_scene) {
    return &((Scene_Data__Game*)p_scene->p_scene_data)
            ->timer_for__hud_notification__u8;
}

#endif
