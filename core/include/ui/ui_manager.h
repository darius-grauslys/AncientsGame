#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void initialize_ui_manager(
        UI_Manager *p_ui_manager);

void poll_ui_manager__update(
        UI_Manager *p_ui_manager,
        Game *p_game);

static inline
Index__u16 get_index_of__p_ui_element_in__ui_manager(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element) {
    return (Index__u16)(
            p_ui_element 
            - p_ui_manager->ui_elements)
        /(sizeof(UI_Element));
}

UI_Element *allocate_ui_element_from__ui_manager(
        UI_Manager *p_ui_manager);

static inline
UI_Element *allocate_ui_element_from__ui_manager_in__succession(
        UI_Manager *p_ui_manager,
        UI_Element *p_predecessor) {
    p_predecessor->p_next =
        allocate_ui_element_from__ui_manager(p_ui_manager);
    return p_predecessor->p_next;
}

static inline
UI_Element *allocate_ui_element_from__ui_manager_as__child(
        UI_Manager *p_ui_manager,
        UI_Element *p_parent) {
    p_parent->p_child =
        allocate_ui_element_from__ui_manager(p_ui_manager);
    return p_parent->p_child;
}

void allocate_many_ui_elements_from__ui_manager(
        UI_Manager *p_ui_manager,
        UI_Element **p_ptr_buffer,
        Quantity__u8 quantity_of__ui_elements_in__ptr_buffer
        );

UI_Element *allocate_many_ui_elements_from__ui_manager_in__succession(
        UI_Manager *p_ui_manager,
        Quantity__u8 quantity_of__ui_elements_to__allocate
        );

UI_Element *allocate_many_ui_elements_from__ui_manager_as__recursive_children(
        UI_Manager *p_ui_manager,
        Quantity__u8 quantity_of__ui_elements_to__allocate
        );

void release__ui_element_from__ui_manager(
        UI_Element *p_ui_element,
        Game *p_game);

void release_all__ui_elements_from__ui_manager(
        UI_Manager *p_ui_manager,
        Game *p_game);

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
