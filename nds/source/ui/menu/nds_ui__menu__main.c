#include <ui/menu/nds_ui__menu__main.h>
#include <defines.h>
#include <platform_defines.h>
#include <nds.h>

#include <assets/ui/ui_map_main_menu.h>

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

void NDS_set_ui_manager_to__menu(
        UI_Manager *p_ui_manager) {
    release_all__ui_elements_from__ui_manager(
            p_ui_manager);

    for (Quantity__u8 i=0;i<3;i++) {
        UI_Element *p_button =
            get_new__ui_element_from__ui_manager(
                    p_ui_manager);
        initialize_ui_button(
                p_button,
                80, 24);
        set_hitbox__position_with__3i32F4(
                &p_button->ui_bounding_box__aabb,
                get_vector__3i32F4_using__i32(52, 72 + 44 * i, 0));
        switch (i) {
            case 0:
                set_ui_element__clicked_handler(
                        p_button, 
                        m_main_menu__singleplayer_button__clicked_handler);
                break;
            case 1:
                set_ui_element__clicked_handler(
                        p_button, 
                        m_main_menu__multiplayer_button__clicked_handler);
                break;
            case 2:
                set_ui_element__clicked_handler(
                        p_button, 
                        m_main_menu__settings_button__clicked_handler);
                break;
        }
    }

    UI_Element *p_button =
        get_new__ui_element_from__ui_manager(
                p_ui_manager);

    initialize_ui_button(
            p_button,
            104, 104);
    set_ui_element__clicked_handler(
            p_button, 
            m_main_menu__play_button__clicked_handler);
    set_ui_element_as__disabled(
            p_button);

    set_hitbox__position_with__3i32F4(
            &p_button->ui_bounding_box__aabb, 
            get_vector__3i32F4_using__i32(184, 118, 0));
}

void NDS_set_ui_background_to__menu_main(
        PLATFORM_Gfx_Context *p_gfx_context) {
	dmaCopy(ui_map_main_menuMap, 
            p_gfx_context->background_ui
            .gfx_map,
            ui_map_main_menuMapLen);
	dmaCopy(ui_map_main_menuMap, 
            p_gfx_context->background_ui__overlay
            .gfx_map,
            ui_map_main_menuMapLen);
}
