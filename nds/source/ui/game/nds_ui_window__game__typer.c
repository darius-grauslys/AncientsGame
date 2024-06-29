#include <ui/game/nds_ui_window__game__typer.h>
#include <ui/nds_ui.h>
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
    NDS_allocate_ui_for__game_hud(p_game);
    UI_Element *p_ui_itterator = 0;
    UI_Element *p_ui_itterator_child = 0;
    UI_Manager *p_ui_manager = get_p_ui_manager_from__game(p_game);
    UI_Element *p_hide = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_hide, 32, 16, get_vector__3i32(196 + 0, 64 + 0, 0), m_ui_button__clicked_handler__default);
    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 12);
    for (Index__u32 index_of__itteration__2=0;itterate_to_next__ui_element(&p_ui_itterator);index_of__itteration__2++) {
        initialize_ui_element_as__button(p_ui_itterator, 14, 12, get_vector__3i32(27 + 15* index_of__itteration__2, 112 + 0* index_of__itteration__2, 0), m_ui_button__clicked_handler__default);
    }

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 10);
    for (Index__u32 index_of__itteration__3=0;itterate_to_next__ui_element(&p_ui_itterator);index_of__itteration__3++) {
        initialize_ui_element_as__button(p_ui_itterator, 14, 12, get_vector__3i32(33 + 15* index_of__itteration__3, 125 + 0* index_of__itteration__3, 0), m_ui_button__clicked_handler__default);
    }

    UI_Element *p_backspace = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_backspace, 29, 12, get_vector__3i32(183 + 0, 125 + 0, 0), m_ui_button__clicked_handler__default);


    UI_Element *p_shift = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_shift, 18, 12, get_vector__3i32(20 + 0, 138 + 0, 0), m_ui_button__clicked_handler__default);

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 9);
    for (Index__u32 index_of__itteration__3=0;itterate_to_next__ui_element(&p_ui_itterator);index_of__itteration__3++) {
        initialize_ui_element_as__button(p_ui_itterator, 14, 12, get_vector__3i32(39 + 15* index_of__itteration__3, 138 + 0* index_of__itteration__3, 0), m_ui_button__clicked_handler__default);
    }

    UI_Element *p_send = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_send, 29, 12, get_vector__3i32(174 + 0, 138 + 0, 0), m_ui_button__clicked_handler__default);


    UI_Element *p_sym = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_sym, 23, 12, get_vector__3i32(20 + 0, 151 + 0, 0), m_ui_button__clicked_handler__default);

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 10);
    for (Index__u32 index_of__itteration__3=0;itterate_to_next__ui_element(&p_ui_itterator);index_of__itteration__3++) {
        initialize_ui_element_as__button(p_ui_itterator, 14, 12, get_vector__3i32(44 + 15* index_of__itteration__3, 151 + 0* index_of__itteration__3, 0), m_ui_button__clicked_handler__default);
    }


    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__itteration__3=0;itterate_to_next__ui_element(&p_ui_itterator);index_of__itteration__3++) {
        initialize_ui_element_as__button(p_ui_itterator, 14, 12, get_vector__3i32(54 + 15* index_of__itteration__3, 164 + 0* index_of__itteration__3, 0), m_ui_button__clicked_handler__default);
    }

    UI_Element *p_space = allocate_ui_element_from__ui_manager(p_ui_manager);
    initialize_ui_element_as__button(p_space, 59, 12, get_vector__3i32(84 + 0, 164 + 0, 0), m_ui_button__clicked_handler__default);

    p_ui_itterator = allocate_many_ui_elements_from__ui_manager_in__succession(p_ui_manager, 2);
    for (Index__u32 index_of__itteration__3=0;itterate_to_next__ui_element(&p_ui_itterator);index_of__itteration__3++) {
        initialize_ui_element_as__button(p_ui_itterator, 14, 12, get_vector__3i32(144 + 15* index_of__itteration__3, 164 + 0* index_of__itteration__3, 0), m_ui_button__clicked_handler__default);
    }


}
