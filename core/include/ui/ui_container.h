#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H

#include <defines.h>

void initialize_ui_element_as__container(
        UI_Element *p_ui_container,
        UI_Container_Entries *p_entries
        );

void remove_all_ui_elements_from__ui_container(
        UI_Element *p_ui_container);

void add_ui_element_to__ui_container(
        UI_Element *p_ui_container);

#endif
