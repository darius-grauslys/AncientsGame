#ifndef UI_SLIDER_H
#define UI_SLIDER_H
#include "defines_weak.h"
#include <defines.h>

void initialize_ui_element_as__slider(
        UI_Element *p_ui_slider,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Dragged m_ui_dragged_handler,
        bool is_snapped_x_or_y__axis);

void m_ui_slider__dragged_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game);

#endif
