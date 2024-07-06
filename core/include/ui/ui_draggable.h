#ifndef UI_DRAGGABLE_H
#define UI_DRAGGABLE_H
#include <defines.h>
#include <ui/ui_element.h>

// TODO: move to private header
void initialize_ui_element_as__draggable(
        UI_Element *p_ui_draggable,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Dragged m_ui_dragged_handler);

void m_ui_draggable__dragged_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game);

#endif
