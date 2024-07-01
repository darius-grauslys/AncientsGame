#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include "defines_weak.h"
#include <defines.h>

void initialize_ui_element_as__button(
        UI_Element *p_ui_button,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Clicked m_ui_clicked_handler);

void m_ui_button__clicked_handler__default(
        UI_Element *p_this_button,
        Game *p_game);

void m_ui_button__held_handler__default(
        UI_Element *p_this_button,
        Game *p_game);

static inline
bool is_ui_button__toggleable(UI_Element *p_ui_button) {
    return (bool)(p_ui_button->ui_button_flags
        & UI_BUTTON_FLAGS__BIT_IS_TOGGLEABLE);
}

static inline
bool is_ui_button__toggled(UI_Element *p_ui_button) {
    return (bool)(p_ui_button->ui_button_flags
        & UI_BUTTON_FLAGS__BIT_IS_TOGGLED);
}

static inline
void set_ui_button_as__toggleable(UI_Element *p_ui_button) {
    p_ui_button->ui_button_flags |=
        UI_BUTTON_FLAGS__BIT_IS_TOGGLEABLE;
}

static inline
void set_ui_button_as__toggled(UI_Element *p_ui_button) {
    p_ui_button->ui_button_flags |=
        UI_BUTTON_FLAGS__BIT_IS_TOGGLED;
}

static inline
void set_ui_button_as__untoggled(UI_Element *p_ui_button) {
    p_ui_button->ui_button_flags &=
        ~UI_BUTTON_FLAGS__BIT_IS_TOGGLED;
}

static inline
void set_ui_button_as__non_toggleable(UI_Element *p_ui_button) {
    p_ui_button->ui_button_flags &=
        ~UI_BUTTON_FLAGS__BIT_IS_TOGGLEABLE;
    set_ui_button_as__untoggled(p_ui_button);
}

static inline
void set_ui_button_as__toggled_or__not_toggled(
        UI_Element *p_ui_button,
        bool is_toggled_or__not_toggled) {
    if (is_toggled_or__not_toggled) {
        set_ui_button_as__toggled(p_ui_button);
    } else {
        set_ui_button_as__untoggled(p_ui_button);
    }
}

static inline
void set_ui_button_as__toggleable_or__non_toggleable(
        UI_Element *p_ui_button,
        bool is_toggleable_or__non_toggleable) {
    if (is_toggleable_or__non_toggleable) {
        set_ui_button_as__toggleable(p_ui_button);
    } else {
        set_ui_button_as__non_toggleable(p_ui_button);
    }
}

static inline
bool toggle_ui_button(UI_Element *p_ui_button) {
    bool should_be_toggled_or__not_toggled =
        !is_ui_button__toggled(p_ui_button);
    set_ui_button_as__toggled_or__not_toggled(
            p_ui_button, 
            should_be_toggled_or__not_toggled);
    return should_be_toggled_or__not_toggled;
}

#endif
