#ifndef UI_INVENTORY_STATION_H
#define UI_INVENTORY_STATION_H

#include "defines.h"

void allocate_ui_station_inventory_for__ui_element_container(
        Game *p_game,
        Graphics_Window *p_gfx_window,
        Station_Inventory_Map *p_station_inventory_map,
        UI_Element *p_ui_element__inventory_slot__requirements,
        UI_Element *p_ui_element__inventory_slot__recipe_and_tools);

#endif
