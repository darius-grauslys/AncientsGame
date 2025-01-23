#ifndef UI_DROP_ZONE__EQUIPMENT_SLOT_H
#define UI_DROP_ZONE__EQUIPMENT_SLOT_H

#include "defines_weak.h"
#include <defines.h>

void initialize_ui_element_as__drop_zone__equipment_slot(
        UI_Element *p_ui_drop_zone__equipment_slot,
        Quantity__u8 width__u8,
        Quantity__u8 height__u8,
        Vector__3i32 position__3i32,
        Serialized_Item_Stack_Ptr s_item_stack_ptr);

void m_ui_drop_zone__receive_drop_handler__equipment_slot(
        UI_Manager *p_ui_manager,
        UI_Element *p_this_draggable,
        UI_Element *p_ui_element__dropped,
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        Input *p_input);

#endif
