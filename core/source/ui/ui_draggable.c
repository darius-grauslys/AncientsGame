#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_element.h"
#include <ui/ui_draggable.h>

void initialize_ui_draggable(
        UI_Element *p_ui_draggable,
        m_UI_Dragged m_ui_dragged_handler,
        Quantity__u8 width,
        Quantity__u8 height) {
    initialize_ui_element(
            p_ui_draggable, 
            UI_Element_Kind__Draggable, 
            UI_FLAGS__BIT_IS_ENABLED, 
            width, height);
    p_ui_draggable->m_ui_dragged_handler =
        m_ui_dragged_handler;
}

void m_ui_draggable__dragged_handler__default(
        UI_Element *p_this_draggable,
        Game *p_game) {
    Vector__3i32F4 *p_position = 
        &p_this_draggable->ui_bounding_box__aabb.position__3i32F4;
    *p_position =
        vector_3i32_to__vector_3i32F4(p_game->input.cursor__3i32);
    p_position->x__i32F4 -= 
        p_this_draggable->ui_bounding_box__aabb.width__quantity_u32 >> 1;
    p_position->y__i32F4 -= 
        p_this_draggable->ui_bounding_box__aabb.height__quantity_u32 >> 1;
}
