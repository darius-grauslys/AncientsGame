#include <ui/menu/nds_ui__menu__main.h>
#include <defines.h>
#include <platform_defines.h>
#include <nds.h>

#include <assets/ui/default/ui_map_main_menu.h>

#include "collisions/hitbox_aabb.h"
#include "defines_weak.h"
#include "ui/nds_ui.h"
#include "ui/ui_button.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "game.h"
#include "scene/scene_manager.h"
#include "vectors.h"

#include "ui/menu/nds_ui__menu.h"

UI_Element *NDS_allocate_ui_for__ui_window__main_menu(
        Game *p_game) {
    UI_Manager *p_ui_manager =
        get_p_ui_manager_from__game(p_game);
    for (Quantity__u8 i=0;i<3;i++) {
        UI_Element *p_button =
            allocate_ui_element_from__ui_manager(
                    p_ui_manager);
        m_UI_Clicked m_ui_clicked_handler;
        switch (i) {
            case 0:
                m_ui_clicked_handler = 
                    m_main_menu__singleplayer_button__clicked_handler;
                break;
            case 1:
                m_ui_clicked_handler = 
                    m_main_menu__multiplayer_button__clicked_handler;
                break;
            case 2:
                m_ui_clicked_handler = 
                    m_main_menu__settings_button__clicked_handler;
                break;
        }
        initialize_ui_element_as__button(
                p_button,
                80, 24,
                get_vector__3i32(52, 72 + 44 * i, 0),
                m_ui_clicked_handler);
    }

    UI_Element *p_button =
        allocate_ui_element_from__ui_manager(
                p_ui_manager);

    initialize_ui_element_as__button(
            p_button,
            104, 104,
            get_vector__3i32(184, 118, 0),
            m_main_menu__play_button__clicked_handler);
    set_ui_element_as__disabled(
            p_button);
}

void NDS_set_ui_background_to__menu_main(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_main_menuMap, 
            p_gfx_context->backgrounds__sub[0]
            .gfx_map,
            ui_map_main_menuMapLen);
	dmaCopy(ui_map_main_menuMap, 
            p_gfx_context->backgrounds__sub[1]
            .gfx_map,
            ui_map_main_menuMapLen);
}
