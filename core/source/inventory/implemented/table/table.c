#include "defines.h"
#include "defines_weak.h"
#include "inventory/item.h"
#include "inventory/item_manager.h"
#include "numerics.h"
#include <inventory/implemented/table/table.h>

void register_into__item_manager__table_into__item_manager(
        Item_Manager *p_item_manager) {
    register_item_in__item_manager(
            p_item_manager, 
            Item_Kind__Table, 
            get_item(
                Item_Kind__Table, 
                ITEM_USAGE_FLAGS__NONE, 
                ITEM_FILTER_FLAG__INTERACTABLE, 
                i32_to__i32F20(40), 
                0, 
                0, 
                0));
}
