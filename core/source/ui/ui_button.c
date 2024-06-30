#include "debug/debug.h"
#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_element.h"
#include <ui/ui_button.h>

void initialize_ui_element_as__button(
        UI_Element *p_ui_button,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Clicked m_ui_button__clicked_handler) {
    initialize_ui_element(
            p_ui_button, 
            UI_Element_Kind__Button, 
            p_ui_button->ui_flags,
            width__u8, 
            height__u8,
            position__3i32);
    set_ui_element__clicked_handler(
            p_ui_button, 
            m_ui_button__clicked_handler);
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
    debug_info__verbose("Button clicked %p", p_this_button);
}

void m_ui_button__held_handler__default(
        UI_Element *p_this_button,
        Game *p_game) {
    p_this_button->button__is_held_down = true;
}
