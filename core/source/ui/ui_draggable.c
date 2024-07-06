#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_element.h"
#include <ui/ui_draggable.h>

void initialize_ui_element_as__draggable(
        UI_Element *p_ui_draggable,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        m_UI_Dragged m_ui_dragged_handler) {
    initialize_ui_element(
            p_ui_draggable, 
            p_ui_draggable->p_parent,
            p_ui_draggable->p_child,
            p_ui_draggable->p_next,
            UI_Element_Kind__Draggable, 
            p_ui_draggable->ui_flags, 
            width__u8, 
            height__u8,
            position__3i32);
    set_ui_element__dragged_handler(
            p_ui_draggable, 
            m_ui_dragged_handler);
}

void m_ui_draggable__dragged_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game) {
    Vector__3i32 position =
        p_game->input.cursor__3i32;
    position.x__i32 -= 
      p_this_draggable->ui_bounding_box__aabb.width__quantity_u32 >> 1;
    position.y__i32 -= 
        p_this_draggable->ui_bounding_box__aabb.height__quantity_u32 >> 1;

    set_ui_element__position(
            p_this_draggable, 
            position);
}
