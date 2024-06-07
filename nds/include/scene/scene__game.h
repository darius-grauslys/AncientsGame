#ifndef SCENE__GAME_H
#define SCENE__GAME_H

#include <defines.h>

void initialize_scene_as__game(Scene *p_scene);

enum Game_Scene_UI_State {
    Game_Scene_UI_State__Idle,
    Game_Scene_UI_State__Equip,
    Game_Scene_UI_State__Ground,
    Game_Scene_UI_State__Work,
};

typedef struct Scene_Data__Game_t {
    enum Game_Scene_UI_State ui_state;
    enum Game_Scene_UI_State button_states[3];
    UI_Element *p_ui_state_buttons[3];

    Timer__u8 timer_for__hud_notification__u8;
} Scene_Data__Game;

#endif
