#include <ui/game/nds_ui_window__game__labor.h>
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

UI_Element *NDS_allocate_ui_for__nds_ui_window__game__labor(Game *p_game){
    UI_Element *p_ui_iterator = 0;
    UI_Element *p_ui_iterator_previous_previous = 0;
    UI_Element *p_ui_iterator_previous = 0;
    UI_Element *p_ui_iterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
NDS_allocate_ui_for__nds_ui_window__game__hud(p_game);
    toggle_ui_button(get_p_ui_element_by__index_from__ui_manager(p_ui_manager, 2));
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 5);
    for (Index__u32 index_of__iteration__2=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__2++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__button(p_ui_iterator, 8, 8, get_vector__3i32(64 + 0* index_of__iteration__2, 104 + 16* index_of__iteration__2, 0), m_ui_button__clicked_handler__default, false, false);
    }

    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 5);
    for (Index__u32 index_of__iteration__2=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__2++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__button(p_ui_iterator, 8, 8, get_vector__3i32(80 + 0* index_of__iteration__2, 104 + 16* index_of__iteration__2, 0), m_ui_button__clicked_handler__default, false, false);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,8);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 5);
    for (Index__u32 index_of__iteration__2=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__2++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__button(p_ui_iterator, 8, 8, get_vector__3i32(96 + 0* index_of__iteration__2, 104 + 16* index_of__iteration__2, 0), m_ui_button__clicked_handler__default, false, false);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,13);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 5);
    for (Index__u32 index_of__iteration__2=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__2++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__button(p_ui_iterator, 8, 8, get_vector__3i32(112 + 0* index_of__iteration__2, 104 + 16* index_of__iteration__2, 0), m_ui_button__clicked_handler__default, false, false);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,18);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
    p_ui_iterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 5);
    for (Index__u32 index_of__iteration__2=0;p_ui_iterator;iterate_to_next__ui_element(&p_ui_iterator),index_of__iteration__2++) {
        p_ui_iterator_previous = p_ui_iterator;
        initialize_ui_element_as__button(p_ui_iterator, 8, 8, get_vector__3i32(128 + 0* index_of__iteration__2, 104 + 16* index_of__iteration__2, 0), m_ui_button__clicked_handler__default, false, false);
    }

    p_ui_iterator_previous_previous->p_next = get_p_ui_element_by__index_from__ui_manager(p_ui_manager,23);
    p_ui_iterator_previous_previous = p_ui_iterator_previous;
}
