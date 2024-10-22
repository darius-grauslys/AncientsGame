#ifndef NDS_UI__INVENTORY_COLUMN_H
#define NDS_UI__INVENTORY_COLUMN_H

#include <defines.h>

///
/// Returns true on failure.
///
bool NDS_load_ui_item_stack(
        Game *p_game,
        PLATFORM_Graphics_Window *p_PLATFORM_graphics_window,
        UI_Manager *p_ui_manager,
        Item_Stack *p_item_stack,
        UI_Element *p_ui_element__inventory_slot);

void NDS_load_ui_inventory_column_for__inventory(
        Game *p_game,
        UI_Element *p_ui_element__inventory_column,
        Inventory *p_inventory);

#endif
