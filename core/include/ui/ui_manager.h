#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "defines_weak.h"
#include <defines.h>

void init_ui_manager(
        UI_Manager *p_ui_manager);

void poll_ui_manager__update(
        UI_Manager *p_ui_manager,
        Game *p_game);

UI_Element *get_new__ui_element(
        UI_Manager *p_ui_manager,
        enum UI_Element_Kind kind_of_ui_element,
        Quantity__u8 width,
        Quantity__u8 height);

void release__ui_element(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element);

///
/// You will want to call this whenever you're implementing a
/// parent/child UI_Element relationship. OR if one UI is
/// LOGICALLY layered about the other.
///
/// TODO: add helper to change visual layering.
///
void raise_priority_of_this__ui_element__with_respect_to_other__ui_element(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element__this,
        UI_Element *p_ui_element__other);

#endif
