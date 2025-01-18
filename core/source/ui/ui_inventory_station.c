#include "ui/ui_inventory_station.h"
#include "defines.h"
#include "platform.h"
#include "ui/ui_inventory_column.h"
#include "ui/ui_manager.h"

void allocate_ui_station_inventory_for__ui_element_container(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        Station_Inventory_Map *p_station_inventory_map,
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element__inventory_slot__requirements,
        UI_Element *p_ui_element__inventory_slot__recipe_and_tools) {
    Index__u32 index_of__inventory_column_slot = 0;

    UI_Element *p_ui_element__current_inventory_slot =
        p_ui_element__inventory_slot__requirements;

    do {
        Item_Stack *p_item_stack =
            &p_station_inventory_map
            ->p_item_stack__required_items[
                index_of__inventory_column_slot];
        allocate_ui_item_stack(
                p_gfx_context, 
                p_gfx_window, 
                p_ui_manager,
                p_item_stack, 
                p_ui_element__current_inventory_slot);
    } while (iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot
            && index_of__inventory_column_slot++
            < ITEM_REQUIREMENT_MAX_QUANTITY_OF);

    p_ui_element__current_inventory_slot =
        p_ui_element__inventory_slot__recipe_and_tools;

    allocate_ui_item_stack(
            p_gfx_context, 
            p_gfx_window, 
            p_ui_manager,
            p_station_inventory_map
            ->p_item_stack__recipe, 
            p_ui_element__current_inventory_slot);
    if (!iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot) {
        return;
    }
    allocate_ui_item_stack(
            p_gfx_context, 
            p_gfx_window, 
            p_ui_manager,
            p_station_inventory_map
            ->p_item_stack__tool_one, 
            p_ui_element__current_inventory_slot);
    if (!iterate_to_next__ui_element(
                &p_ui_element__current_inventory_slot)
            && p_ui_element__current_inventory_slot) {
        return;
    }
    allocate_ui_item_stack(
            p_gfx_context, 
            p_gfx_window, 
            p_ui_manager,
            p_station_inventory_map
            ->p_item_stack__tool_two, 
            p_ui_element__current_inventory_slot);
}
