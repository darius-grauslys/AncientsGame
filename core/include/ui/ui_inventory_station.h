#ifndef UI_INVENTORY_STATION_H
#define UI_INVENTORY_STATION_H

#include "defines.h"

void allocate_ui_station_inventory_for__ui_element_container(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        Station_Inventory_Map *p_station_inventory_map,
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element__inventory_slot__requirements,
        UI_Element *p_ui_element__inventory_slot__recipe_and_tools);

#endif
