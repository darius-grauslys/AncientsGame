#include "collisions/hitbox_aabb.h"
#include "debug/debug.h"
#include "defines.h"
#include "ui/ui_button.h"
#include "ui/ui_draggable.h"
#include "ui/ui_slider.h"
#include <ui/ui_element.h>
#include <vectors.h>

void initialize_ui_element(
        UI_Element *p_ui_element,
        enum UI_Element_Kind kind_of_ui_element,
        UI_Flags__u8 ui_flags,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32) {
    p_ui_element->p_ui_data = 0;
    p_ui_element->ui_identifier = 
        IDENTIFIER__UNKNOWN__u16;
    p_ui_element->the_kind_of_ui_element__this_is =
        kind_of_ui_element;
    p_ui_element->ui_flags = ui_flags;
    initialize_hitbox(
            &p_ui_element->ui_bounding_box__aabb, 
            width__u8, 
            height__u8, 
            vector_3i32_to__vector_3i32F4(position__3i32));
    p_ui_element->m_ui_clicked_handler = 0;
    p_ui_element->m_ui_dragged_handler = 0;
    p_ui_element->m_ui_dropped_handler = 0;
    p_ui_element->m_ui_held_handler = 0;
    p_ui_element->m_ui_dispose_handler = 0;
}

