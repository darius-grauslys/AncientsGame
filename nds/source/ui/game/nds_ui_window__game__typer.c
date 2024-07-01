#include <ui/game/nds_ui_window__game__typer.h>
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

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__typer(Game *p_game){
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    
    UI_Element *p_hide = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_hide, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_hide, false);
    set_ui_button_as__toggled_or__not_toggled(p_hide, false);
    set_ui_element__hitbox(p_hide, 32, 16, get_vector__3i32(220 + 0, 68 + 0, 0));

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 12);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_ui_button__clicked_handler__default);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, false);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 14, 12, get_vector__3i32(43 + 15* index_of__itteration__3, 114 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 10);
    for (Index__u32 index_of__itteration__4=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__4++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_ui_button__clicked_handler__default);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, false);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 14, 12, get_vector__3i32(49 + 15* index_of__itteration__4, 127 + 0* index_of__itteration__4, 0));
    }

    UI_Element *p_backspace = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_backspace, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_backspace, false);
    set_ui_button_as__toggled_or__not_toggled(p_backspace, false);
    set_ui_element__hitbox(p_backspace, 27, 12, get_vector__3i32(206 + 0, 127 + 0, 0));


    UI_Element *p_shift = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_shift, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_shift, false);
    set_ui_button_as__toggled_or__not_toggled(p_shift, false);
    set_ui_element__hitbox(p_shift, 18, 12, get_vector__3i32(37 + 0, 140 + 0, 0));

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 9);
    for (Index__u32 index_of__itteration__4=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__4++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_ui_button__clicked_handler__default);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, false);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 14, 12, get_vector__3i32(55 + 15* index_of__itteration__4, 140 + 0* index_of__itteration__4, 0));
    }

    UI_Element *p_send = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_send, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_send, false);
    set_ui_button_as__toggled_or__not_toggled(p_send, false);
    set_ui_element__hitbox(p_send, 27, 12, get_vector__3i32(197 + 0, 140 + 0, 0));


    UI_Element *p_sym = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_sym, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_sym, false);
    set_ui_button_as__toggled_or__not_toggled(p_sym, false);
    set_ui_element__hitbox(p_sym, 22, 12, get_vector__3i32(39 + 0, 153 + 0, 0));

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 10);
    for (Index__u32 index_of__itteration__4=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__4++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_ui_button__clicked_handler__default);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, false);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 14, 12, get_vector__3i32(59 + 15* index_of__itteration__4, 153 + 0* index_of__itteration__4, 0));
    }


    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__itteration__4=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__4++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_ui_button__clicked_handler__default);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, false);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 14, 12, get_vector__3i32(70 + 15* index_of__itteration__4, 166 + 0* index_of__itteration__4, 0));
    }

    UI_Element *p_space = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_space, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_space, false);
    set_ui_button_as__toggled_or__not_toggled(p_space, false);
    set_ui_element__hitbox(p_space, 56, 12, get_vector__3i32(121 + 0, 166 + 0, 0));

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__itteration__4=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__4++) {
        set_ui_element__clicked_handler(p_ui_itterator, m_ui_button__clicked_handler__default);
        set_ui_button_as__toggleable_or__non_toggleable(p_ui_itterator, false);
        set_ui_button_as__toggled_or__not_toggled(p_ui_itterator, false);
        set_ui_element__hitbox(p_ui_itterator, 14, 12, get_vector__3i32(158 + 15* index_of__itteration__4, 166 + 0* index_of__itteration__4, 0));
    }



}
