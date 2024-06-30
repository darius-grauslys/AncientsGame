#include <ui/game/nds_ui_window__game__trade.h>
#include <ui/nds_ui.h>
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
    NDS_allocate_ui_for__game_hud(p_game);
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    UI_Element *p_slider_left = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__dragged_handler(p_slider_left, m_ui_slider__dragged_handler__default);
    set_ui_element__hitbox(p_slider_left, true);
    UI_Element *p_slider_right = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__dragged_handler(p_slider_right, m_ui_slider__dragged_handler__default);
    set_ui_element__hitbox(p_slider_right, true);
    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 1 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 3 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 29 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 31 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 57 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 59 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 85 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 87 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 113 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 115 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 141 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 143 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 169 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 171 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 197 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 199 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(46 + 24* index_of__itteration__2, 225 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(48 + 24* index_of__itteration__2, 227 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 1 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 3 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 29 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 31 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 57 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 59 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 85 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 87 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 113 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 115 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 141 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 143 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 169 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 171 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 197 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 199 + 0* index_of__itteration__2, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__2=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator) && (++index_of__itteration__2)) {
        set_ui_element__dragged_handler(m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(138 + 24* index_of__itteration__2, 225 + 0* index_of__itteration__2, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(140 + 24* index_of__itteration__2, 227 + 0* index_of__itteration__2, 0));
    }

    UI_Element *p_filter_button__usables = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_filter_button__usables, m_ui_button__clicked_handler__default);
    set_ui_element__hitbox(p_filter_button__usables, 16, 12, get_vector__3i32(52 + 0, 170 + 0, 0));
    UI_Element *p_filter_button__wearables = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_filter_button__wearables, m_ui_button__clicked_handler__default);
    set_ui_element__hitbox(p_filter_button__wearables, 16, 12, get_vector__3i32(76 + 0, 170 + 0, 0));
    UI_Element *p_filter_button__consumables = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_filter_button__consumables, m_ui_button__clicked_handler__default);
    set_ui_element__hitbox(p_filter_button__consumables, 16, 12, get_vector__3i32(100 + 0, 170 + 0, 0));
}
