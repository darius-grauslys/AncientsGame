#ifndef UI_INVENTORY_EQUIPMENT_H
#define UI_INVENTORY_EQUIPMENT_H

#include "defines.h"
#include "defines_weak.h"

void allocate_ui_equipment_into__ui_element_container(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element,
        Equipment *p_equipment);

#endif
