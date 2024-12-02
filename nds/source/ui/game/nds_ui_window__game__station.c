#include <ui/game/nds_ui_window__game__station.h>
#include <ui/game/nds_ui_window__game__hud.h>
#include <nds.h>
#include <rendering/gfx_context.h>
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
#include <ui/ui_drop_zone__inventory_slot.h>
#include <ui/handlers/inventory/nds_ui_handler__button_craft.h>
// THIS CODE IS AUTO GENERATED. Go to ./nds/assets/ui/xml/ instead of modifying this file.

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__station(Game *p_game, UI_Manager *p_ui_manager){
    UI_Element *p_ui_iterator = 0;
    UI_Element *p_ui_iterator_previous_previous = 0;
    UI_Element *p_ui_iterator_previous = 0;
    UI_Element *p_ui_iterator_child = 0;
NDS_allocate_ui_for__nds_ui_window__game__hud(p_game, p_ui_manager);
    toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 0));
    UI_Element *p_slider = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__slider(p_slider, 16, 80, get_vector__3i32(228 + 0, 132 + 0, 0), get_vector__3i32(0 + 0, 176 + 0, 0 + 0), m_ui_slider__dragged_handler__gfx_window__default, true);

NDS_allocate_sprite_for__ui_slider(
    get_p_PLATFORM_gfx_context_from__game(p_game),
    p_slider);
    p_slider->p_ui_data = 
    NDS_get_p_PLATFORM_gfx_window_of__UI__SCROLL(
    get_p_PLATFORM_gfx_context_from__game(p_game));

    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 3);
    for (Index__u32 index_of__iteration__2=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__2++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 20, 20, get_vector__3i32(140 + 0* index_of__iteration__2, 100 + 32* index_of__iteration__2, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_RECIPE_AND_TOOLS_4));
    }

    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 20, 20, get_vector__3i32(28 + 32* index_of__iteration__3, 124 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_RECIPE_AND_TOOLS_4));
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 20, 20, get_vector__3i32(28 + 32* index_of__iteration__3, 156 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_RECIPE_AND_TOOLS_4));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,9);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;

    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 103 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 131 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,13);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 159 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,15);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 187 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,17);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 215 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,19);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 243 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,21);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 271 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,23);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 299 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,25);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__iteration__3=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__3++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__drop_zone(p_ui_iterator, 23, 27, get_vector__3i32(174 + 24* index_of__iteration__3, 327 + 0* index_of__iteration__3, 0), m_ui_drop_zone__receive_drop_handler__inventory_slot);
        set_ui_element__p_data(
        p_ui_iterator,
        get_p_ui_element_by__index_from__ui_manager(
        p_ui_manager,
        NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,27);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;

set_ui_element_as__the_parent_of__this_ui_element(
    p_ui_manager,
    p_slider,
    get_p_ui_element_by__index_from__ui_manager(
    p_ui_manager,
    NDS_UI_WINDOW__GAME__STATION_P_INVENTORY_COLUMN_11));

    p_ui_iterator = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_ui_iterator, 32, 16, get_vector__3i32(100 + 0, 164 + 0, 0), m_NDS_ui_button__click_handler__craft, false, false);
}
