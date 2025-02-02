#ifndef UI_INVENTORY_COLUMN_H
#define UI_INVENTORY_COLUMN_H

#include "defines.h"

bool allocate_ui_item_stack(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
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
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_gfx_window,
        UI_Element *p_ui_element,
        Inventory *p_inventory);

#endif
