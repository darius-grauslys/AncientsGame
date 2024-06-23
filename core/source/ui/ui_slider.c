#include "ui/ui_element.h"
#include <ui/ui_slider.h>

void initialize_ui_element_as__slider(
        UI_Element *p_ui_slider,
        m_UI_Dragged m_ui_dragged_handler,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        bool is_snapped_x_or_y__axis) {
    initialize_ui_element(
            p_ui_slider, 
            UI_Element_Kind__Slider, 
            p_ui_slider->ui_flags, 
            width__u8, 
            height__u8, 
            position__3i32);
    set_ui_element__dragged_handler(
            p_ui_slider, 
            m_ui_dragged_handler);
    if (is_snapped_x_or_y__axis) {
        set_ui_element_as__snapped_x_axis(p_ui_slider);
    } else {
        set_ui_element_as__snapped_y_axis(p_ui_slider);
    }
}
