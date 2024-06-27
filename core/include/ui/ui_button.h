#ifndef UI_BUTTON_H
#define UI_BUTTON_H
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

#endif
