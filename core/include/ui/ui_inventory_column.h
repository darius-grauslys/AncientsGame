#ifndef UI_INVENTORY_COLUMN_H
#define UI_INVENTORY_COLUMN_H

#include "defines.h"
#include "defines_weak.h"

bool allocate_ui_item_stack(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_graphics_window,
        World *p_world,
        UI_Manager *p_ui_manager,
        Item_Stack *p_item_stack,
        UI_Element *p_ui_element__inventory_slot);

///
/// For a series of p_next entries in the given ui_element,
/// fill as much of it as possible with the corresponding
/// inventory data.
///
/// If successful, the UI will reflect the given inventory
/// and UI events will modify the inventory state!
///
/// TODO: ensure that the core implementation leverages Game_Actions
/// to relay state modification.
///
void allocate_ui_inventory_column_into__ui_element_container(
        Gfx_Context *p_gfx_context,
        Graphics_Window *p_gfx_window,
        World *p_world,
        UI_Manager *p_ui_manager,
        UI_Element *p_ui_element,
        Inventory *p_inventory);

#endif
