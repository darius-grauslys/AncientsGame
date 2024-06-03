#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_element.h"
#include <ui/ui_button.h>

void initialize_ui_button(
        UI_Element *p_ui_button,
        Quantity__u8 width,
        Quantity__u8 height) {
    initialize_ui_element(
            p_ui_button, 
            UI_Element_Kind__Button, 
            p_ui_button->ui_flags,
            width, 
            height);
    set_ui_element__clicked_handler(
            p_ui_button, 
            m_ui_button__clicked_handler__default);
}

void m_ui_button__clicked_handler__default(
        UI_Element *p_this_button,
        Game *p_game) {
    p_this_button->button__is_held_down = 
        false
        || (p_this_button->button__is_toggleable
                && !p_this_button->button__is_held_down
                )
        ;
}

void m_ui_button__held_handler__default(
        UI_Element *p_this_button,
        Game *p_game) {
    p_this_button->button__is_held_down = true;
}
