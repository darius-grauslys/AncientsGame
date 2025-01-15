#ifndef UI_INVENTORY_EQUIPMENT_H
#define UI_INVENTORY_EQUIPMENT_H

#include "defines.h"
#include "defines_weak.h"

void allocate_ui_equipment_into__ui_element_container(
        Game *p_game,
        Graphics_Window *p_gfx_window,
        UI_Element *p_ui_element,
        Equipment *p_equipment);

#endif
