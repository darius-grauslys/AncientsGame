#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void init_ui_manager(
        UI_Manager *p_ui_manager);

void poll_ui_manager__update(
        UI_Manager *p_ui_manager,
        Game *p_game);

UI_Element *get_new__ui_element_from__ui_manager(
        UI_Manager *p_ui_manager);

void get_many_new__ui_elements_from__ui_manager(
        UI_Manager *p_ui_manager,
        UI_Element **p_ptr_buffer,
        Quantity__u8 quantity_of__ui_elements_in__ptr_buffer
        );

void release__ui_element_from__ui_manager(
        UI_Element *p_ui_element,
        UI_Manager *p_ui_manager);

void release_all__ui_elements_from__ui_manager(
        UI_Manager *p_ui_manager);

///
/// You will want to call this whenever you're implementing a
/// parent/child UI_Element relationship. OR if one UI is
/// LOGICALLY layered about the other.
///
/// TODO: add helper to change visual layering.
///
void swap_priority_of__ui_elenents_within__ui_manager(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element__this,
        UI_Element *p_ui_element__other);

#endif
