#ifndef UI_BUTTON_H
#define UI_BUTTON_H
#include <defines.h>

// TODO: move to private header
void initialize_ui_button(
        UI_Element *p_ui_button,
        Quantity__u8 width,
        Quantity__u8 height);

void m_ui_button__clicked_handler__default(
        UI_Element *p_this_button,
        Game *p_game);

void m_ui_button__held_handler__default(
        UI_Element *p_this_button,
        Game *p_game);

#endif
