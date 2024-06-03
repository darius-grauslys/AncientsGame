#ifndef UI_SLIDER_H
#define UI_SLIDER_H
#include "defines_weak.h"
#include <defines.h>

// TODO: move to private header
void initialize_ui_slider(
        UI_Element *p_ui_slider,
        Quantity__u8 width,
        Quantity__u8 height);

void f_ui_slider__dragged_handler__default(
        UI_Element *p_this_slider);

static void inline set_ui_slider__dragged_handler(
        UI_Element *p_ui_slider,
        m_UI_Dragged m_ui_dragged_handler) {
    p_ui_slider->m_ui_dragged_handler =
        m_ui_dragged_handler;
}

#endif
