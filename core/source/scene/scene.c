#include "debug/debug.h"
#include "defines_weak.h"
#include "input/input.h"
#include "ui/ui_element.h"
#include <scene/scene.h>
#include <game.h>

void m_enter_scene_handler__default(
        Scene *p_this_scene,
        Game *p_game) {
    while (p_game->scene_manager.p_active_scene
            == p_this_scene) {
        manage_game__pre_render(p_game);
        if (is_input__click_released(&p_game->input)) {
            debug_info__verbose("scene.c, SCENE_UI_CLICK");
            debug_info__verbose("click: (%d, %d)",
                    p_game->input.cursor__old__3i32.x__i32,
                    p_game->input.cursor__old__3i32.y__i32);
            for (Quantity__u8 ui_index=0;
                    ui_index<p_game->ui_manager
                    .quantity_of__ui_elements__quantity_u8;
                    ui_index++) {
                UI_Element *p_ui_element =
                    p_game->ui_manager.ui_element_ptrs[ui_index];

                if (!p_ui_element)
                    continue;
                debug_info__verbose("ui_element: (%d, %d)",
                        get_x_i32_from__p_ui_element(p_ui_element),
                        get_y_i32_from__p_ui_element(p_ui_element)
                        );
            }
        }
        manage_game__post_render(p_game);
    }
}
