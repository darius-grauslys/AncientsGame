#include <ui/game/nds_ui_window__game__idle.h>
#include <ui/game/nds_ui_window__game__hud.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_drop_zone.h>
#include <ui/ui_draggable.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
// THIS CODE IS AUTO GENERATED. Go to ./nds/assets/ui/xml/ instead of modifying this file.

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__idle(Game *p_game){
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    NDS_allocate_ui_for__nds_ui_window__game__hud(p_game);
    UI_Element *p_slider = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_slider, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_slider, false);
    set_ui_button_as__toggled_or__not_toggled(p_slider, false);
    set_ui_element__hitbox(p_slider, 16, 80, get_vector__3i32(228 + 0, 132 + 0, 0));
    UI_Element *p_button__chat = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button__chat, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_button__chat, false);
    set_ui_button_as__toggled_or__not_toggled(p_button__chat, false);
    set_ui_element__hitbox(p_button__chat, 32, 16, get_vector__3i32(220 + 0, 186 + 0, 0));
    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 4);
    for (Index__u32 index_of__itteration__1=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__1++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_ui_button__clicked_handler__default);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, false);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 16, 12, get_vector__3i32(28 + 0* index_of__itteration__1, 96 + 24* index_of__itteration__1, 0));
    }
}
