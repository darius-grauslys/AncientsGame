#include "defines_weak.h"
#include "nds_defines.h"
#include <ui/game/nds_ui_window__game__equip.h>
#include <ui/game/nds_ui_window__game__hud.h>
#include <ui/ui_element.h>
#include <ui/ui_button.h>
#include <ui/ui_drop_zone.h>
#include <ui/ui_draggable.h>
#include <ui/ui_slider.h>
#include <ui/nds_ui__slider.h>
#include <ui/ui_manager.h>
#include <vectors.h>
#include <defines.h>
#include <game.h>
// THIS CODE IS AUTO GENERATED. Go to ./nds/assets/ui/xml/ instead of modifying this file.

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__equip(Game *p_game){
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    NDS_allocate_ui_for__nds_ui_window__game__hud(p_game);toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 0));
    UI_Element *p_slider = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__slider(
            p_slider,
            16, 80,
            get_vector__3i32(196 + 0, 132 + 0, 0),
            m_NDS_ui_slider__dragged_handler_for__backgrounds,
            true);
    NDS_allocate_sprite_for__ui_slider(
            get_p_PLATFORM_gfx_context_from__game(p_game),
            p_slider);
    p_slider->p_ui_data =
        &get_p_PLATFORM_gfx_context_from__game(p_game)
        ->backgrounds__sub[2];

    NDS_Background *p_NDS_background =
        &get_p_PLATFORM_gfx_context_from__game(p_game)
        ->backgrounds__sub[2];
    p_NDS_background->spanning_scroll_lengths__3i32 = (Vector__3i32){0, 176, 0};
    p_NDS_background->starting_position__3i32 = (Vector__3i32){0, 88, 0};

    UI_Element *p_button_filter__usable = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button_filter__usable, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_button_filter__usable, false);
    set_ui_button_as__toggled_or__not_toggled(p_button_filter__usable, false);
    set_ui_element__hitbox(p_button_filter__usable, 16, 16, get_vector__3i32(228 + 0, 104 + 0, 0));

    UI_Element *p_button_filter__wearable = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button_filter__wearable, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_button_filter__wearable, false);
    set_ui_button_as__toggled_or__not_toggled(p_button_filter__wearable, false);
    set_ui_element__hitbox(p_button_filter__wearable, 16, 16, get_vector__3i32(228 + 0, 132 + 0, 0));

    UI_Element *p_button_filter__consumable = allocate_ui_element_from__ui_manager(p_ui_manager);
    set_ui_element__clicked_handler(p_button_filter__consumable, m_ui_button__clicked_handler__default);
    set_ui_button_as__toggleable_or__non_toggleable(p_button_filter__consumable, false);
    set_ui_button_as__toggled_or__not_toggled(p_button_filter__consumable, false);
    set_ui_element__hitbox(p_button_filter__consumable, 16, 16, get_vector__3i32(228 + 0, 160 + 0, 0));

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 15 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 15 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 43 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 43 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 71 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 71 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 99 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 99 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 127 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 127 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 155 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 155 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 183 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 183 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 211 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 211 + 0* index_of__itteration__3, 0));
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__itteration__3=0;p_ui_itterator;itterate_to_next__ui_element(&p_ui_itterator),index_of__itteration__3++) {
        set_ui_element__dragged_handler(p_ui_itterator, m_ui_drop_zone__recieve_drop_handler__default);
        set_ui_element__hitbox(p_ui_itterator, 23, 27, get_vector__3i32(104 + 24* index_of__itteration__3, 239 + 0* index_of__itteration__3, 0));
                p_ui_itterator_child = allocate_ui_element_from__ui_manager_as__child(p_ui_manager, p_ui_itterator);
        set_ui_element__dragged_handler(p_ui_itterator_child, m_ui_draggable__dragged_handler__default);
        set_ui_element__hitbox(p_ui_itterator_child, 18, 22, get_vector__3i32(104 + 24* index_of__itteration__3, 239 + 0* index_of__itteration__3, 0));
    }


}
