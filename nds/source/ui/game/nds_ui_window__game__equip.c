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
#include <nds_defines.h>
#include <game.h>
// THIS CODE IS AUTO GENERATED. Go to ./nds/assets/ui/xml/ instead of modifying this file.

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__equip(Game *p_game){
    UI_Element *p_ui_iterator = 0;
    UI_Element *p_ui_iterator_previous_previous = 0;
    UI_Element *p_ui_iterator_previous = 0;
    UI_Element *p_ui_iterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
NDS_allocate_ui_for__nds_ui_window__game__hud(p_game);
    toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 0));
    UI_Element *p_slider = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__slider(p_slider, 16, 80, get_vector__3i32(196 + 0, 132 + 0, 0), m_NDS_ui_slider__dragged_handler_for__backgrounds, true);

NDS_allocate_sprite_for__ui_slider(
    get_p_PLATFORM_gfx_context_from__game(p_game),
    p_slider);
    NDS_Background *p_NDS_background =
    &get_p_PLATFORM_gfx_context_from__game(p_game)
    ->backgrounds__sub[NDS_BACKGROUND_SLOT__UI__SCROLL];
    p_slider->p_ui_data = p_NDS_background;

    UI_Element *p_button_filter__usable = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_filter__usable, 16, 16, get_vector__3i32(228 + 0, 104 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_button_filter__wearable = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_filter__wearable, 16, 16, get_vector__3i32(228 + 0, 132 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_button_filter__consumable = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_button_filter__consumable, 16, 16, get_vector__3i32(228 + 0, 160 + 0, 0), m_ui_button__clicked_handler__default, false, false);

    UI_Element *p_item_slot__armor = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__drop_zone(p_item_slot__armor, 20, 20, get_vector__3i32(32 + 0, 100 + 0, 0), m_ui_drop_zone__receive_drop_handler__default);

    UI_Element *p_item_slot__main_hand = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__drop_zone(p_item_slot__main_hand, 20, 20, get_vector__3i32(32 + 0, 132 + 0, 0), m_ui_drop_zone__receive_drop_handler__default);

    UI_Element *p_item_slot__off_hand = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__drop_zone(p_item_slot__off_hand, 20, 20, get_vector__3i32(32 + 0, 164 + 0, 0), m_ui_drop_zone__receive_drop_handler__default);

    UI_Element *p_item_slot__consumable_1 = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__drop_zone(p_item_slot__consumable_1, 20, 20, get_vector__3i32(60 + 0, 100 + 0, 0), m_ui_drop_zone__receive_drop_handler__default);

    UI_Element *p_item_slot__consumable_2 = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__drop_zone(p_item_slot__consumable_2, 20, 20, get_vector__3i32(60 + 0, 132 + 0, 0), m_ui_drop_zone__receive_drop_handler__default);

    UI_Element *p_item_slot__consumeable_3 = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__drop_zone(p_item_slot__consumeable_3, 20, 20, get_vector__3i32(60 + 0, 164 + 0, 0), m_ui_drop_zone__receive_drop_handler__default);


    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 15 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 43 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,16);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 71 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,19);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 99 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,22);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 127 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,25);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 155 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,28);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 183 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,31);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 211 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,34);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(104 + 24* index_of__iteration__3, 239 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__default);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,37);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;

set_ui_element_as__the_parent_of__this_ui_element(
    p_ui_manager,
    p_slider,
    get_p_ui_element_by__index_from__ui_manager(
    p_ui_manager,
    NDS_UI_WINDOW__GAME__EQUIP_P_INVENTORY_COLUMN_13));

}
