#ifndef UI_DRAGGABLE_H
#define UI_DRAGGABLE_H
#include <defines.h>

// TODO: move to private header
void initialize_ui_draggable(
        UI_Element *p_ui_draggable,
        m_UI_Dragged m_ui_dragged_handler,
        Quantity__u8 width,
        Quantity__u8 height);

void m_ui_draggable__dragged_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game);

#endif
