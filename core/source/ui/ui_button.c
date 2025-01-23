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
        m_UI_Clicked m_ui_button__clicked_handler,
        bool is_toggleable_or__non_toggleable,
        bool is_toggled_or__not_toggled) {
    initialize_ui_element(
            p_ui_button, 
            p_ui_button->p_parent,
            p_ui_button->p_child,
            p_ui_button->p_next,
            UI_Element_Kind__Button, 
            p_ui_button->ui_flags,
            width__u8, 
            height__u8,
            position__3i32);
    set_ui_element__clicked_handler(
            p_ui_button, 
            m_ui_button__clicked_handler);
    set_ui_button_as__toggleable_or__non_toggleable(
            p_ui_button, 
            is_toggleable_or__non_toggleable);
    set_ui_button_as__toggled_or__not_toggled(
            p_ui_button, 
            is_toggled_or__not_toggled);
}

void m_ui_button__clicked_handler__default(
        UI_Element *p_this_button,
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        Input *p_input) {
}

void m_ui_button__held_handler__default(
        UI_Element *p_this_button,
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        Input *p_input) {
}
