#include "inventory/inventory.h"
#include <inventory/station_inventory_map.h>

void map_station_inventory(
        Inventory *p_station_inventory,
        Station_Inventory_Map *p_station_inventory_map) {
    p_station_inventory_map->p_item_stack__required_items =
        get_p_item_stack_from__inventory_by__index(
                p_station_inventory, 
                0);
    p_station_inventory_map->p_item_stack__recipe =
        get_p_item_stack_from__inventory_by__index(
                p_station_inventory, 
                4);
    p_station_inventory_map->p_item_stack__tool_one =
        get_p_item_stack_from__inventory_by__index(
                p_station_inventory, 
                5);
    p_station_inventory_map->p_item_stack__tool_two =
        get_p_item_stack_from__inventory_by__index(
                p_station_inventory, 
                6);
}
