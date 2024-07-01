#include <ui/game/nds_ui_window__game__trade.h>
#include <ui/game/nds_ui_window__game__hud.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_draggable.h>
#include <ui/ui_drop_zone.h>
#include <ui/ui_slider.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
// THIS CODE IS AUTO GENERATED. Go to ./nds/assets/ui/xml/ instead of modifying this file.

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__trade(Game *p_game){
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    NDS_allocate_ui_for__nds_ui_window__game__hud(p_game);toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 1));
    UI_Element *p_filter_button__usables = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_filter_button__usables, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_filter_button__usables, false);
    set_ui_button_as__toggled_or__not_toggled(p_filter_button__usables, false);
    set_ui_element__hitbox(p_filter_button__usables, 16, 12, get_vector__3i32(60 + 0, 176 + 0, 0));

    UI_Element *p_filter_button__wearables = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_filter_button__wearables, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_filter_button__wearables, false);
    set_ui_button_as__toggled_or__not_toggled(p_filter_button__wearables, false);
    set_ui_element__hitbox(p_filter_button__wearables, 16, 12, get_vector__3i32(84 + 0, 176 + 0, 0));

    UI_Element *p_filter_button__consumables = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_filter_button__consumables, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_filter_button__consumables, false);
    set_ui_button_as__toggled_or__not_toggled(p_filter_button__consumables, false);
    set_ui_element__hitbox(p_filter_button__consumables, 16, 12, get_vector__3i32(108 + 0, 176 + 0, 0));


    UI_Element *p_slider_left = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__dragged_handler(p_slider_left, m_ui_slider__dragged_handler__default);
    set_ui_element__snapped_state(p_slider_left, true);
    set_ui_element__hitbox(p_slider_left, 16, 80, get_vector__3i32(28 + 0, 132 + 0, 0));

    UI_Element *p_slider_right = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__dragged_handler(p_slider_right, m_ui_slider__dragged_handler__default);
    set_ui_element__snapped_state(p_slider_right, true);
    set_ui_element__hitbox(p_slider_right, 16, 80, get_vector__3i32(228 + 0, 132 + 0, 0));

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 15 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 15 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 43 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 43 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 71 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 71 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 99 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 99 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 127 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 127 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 155 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 155 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 183 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 183 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 211 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 211 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(58 + 24* index_of__itteration__3, 239 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(58 + 24* index_of__itteration__3, 239 + 0* index_of__itteration__3, 0));
    }


    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 15 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 15 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 43 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 43 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 71 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 71 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 99 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 99 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 127 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 127 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 155 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 155 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 183 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 183 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 211 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 211 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(150 + 24* index_of__itteration__3, 239 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(150 + 24* index_of__itteration__3, 239 + 0* index_of__itteration__3, 0));
    }


}
