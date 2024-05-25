#ifndef UI_SLIDER_H
#define UI_SLIDER_H
#include <defines.h>

// TODO: move to private header
void init_ui_slider(
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_slider
        );

void f_ui_slider__dragged_handler__default(
        UI_Element *p_this_slider);

static void inline set_ui_slider__dragged_handler(
        UI_Element *p_ui_slider,
        m_UI_Dragged m_ui_dragged_handler) {
    p_ui_slider->m_ui_dragged_handler =
        m_ui_dragged_handler;
}

#endif
